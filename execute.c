/*
   execute . cria um processo progénito e executa um programa
*/
#include "shell.h"

int ultimo (int* numargs, char** args)
{
  if (args[*numargs-1][0]=='&')
  {
    args[*numargs-1]=NULL;
    (*numargs)--;
    return BG;
  }
  /* return FG ou BH definidos no shell.h */
  return FG;
}

/* Detect PIPE SYMBOL in array of Strigs */
int containsPipe (int numArgs, char** args) 
{
  int index;

  for (index=0; index < numArgs; index++)
  {
    if (args[index][0] == '|')
    {
      // fputs("Tem index", stdout);
      return index;
    }
  }
  // returns its index or -1 if does not exist
  return -1;
}

void execute (int numargs, char **args)
{
  int pid, status, fd[2], pidFilho;
  int code = ultimo(&numargs, args);

  if((pid = fork ()) < 0)
  {			
    perror ("forks");
    exit (1);
  }

  if (pid == 0)
  {
    // PIPE
    int index = containsPipe(numargs, args);

    if(index>0)
    {
      printf("pipe detected at index %d\n", index);
      printf("Remove PIPE symbol. Create Pipe. Fork(). Exec in 2 processes\n");
      args[index]=NULL;
      pipe(fd);
      pidFilho=fork();

      if(pidFilho==0)
      {
        // write
        numargs=index;
        fprintf(stderr, "cmd write to pipe: %s numArgs=%d\n", args[0], numargs);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
      }

      else
      {
        // read
        args=args+index+1;
        numargs=numargs-index-1;
        fprintf(stderr, "cmd read from pipe: %s numArgs=%d\n", args[0], numargs);
        dup2(fd[0], STDIN_FILENO);
        close(fd[1]);   
        close(fd[0]);   
      }
    }

    // REDIRECTS
    if(redirects(numargs, args)==-1)  exit(1);
    
    execvp (*args, args);	
    perror (*args);
    exit (1);			
  }
  else		
  {
    if(FG==code)
    {  
      while (wait (&status) != pid)  
      /*spin fazer nada*/ ;
    }
  }
}