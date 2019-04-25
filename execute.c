/*
   execute . cria um processo prog�nito e executa um programa
*/
#include "shell.h"

int ultimo (int numargs, char** args)
{
  if (args[numargs-1][0]=='&')
  {
    args[numargs-1]=NULL;
    return BG;
  }
  return FG;    /* return FG ou BH definidos no shell.h */
}

/* Detect PIPE SYMBOL in array of Strigs */
// returns its index or -1 if does not exist
int containsPipe (int numArgs, char** args) 
{
  int index;

  for (index=0; index < numArgs; index++)
  {
    if (args[index][0] == '|')
    {
      return index;
    }
  }
  return -1;
}

void execute (int numargs, char **args)
{
  int pid, status, index;

  int code = ultimo(numargs, args);

  if ((pid = fork ()) < 0)
    {				/* cria um processo progenito */
      perror ("forks");		/* NOTE: perror() produz uma pequema mensagem
				 * de erro para o stream */
      exit (1);			/* estandardizado de erros que descreve o
				 * ultimo erro encontrado */
      /* durante uma chamada ao sistema ou funcao duma biblioteca */
    }

  if (pid == 0)
  {
    index=containsPipe(numargs, args);
    
    if(index==-1)
      execvp (*args, args);	
    /* NOTE: as versoes execv() e execvp() de execl() sao uteis 
    quando o numero de argumentos não é conhecido. */
    perror (*args); 
	  /* Os argumentos de execv() e execvp() sao o nome do ficheiro 
    a ser executado e um vector de strings que contem os argumentos. 
    O ultimo argument */
    exit (1);			
  }
  				
  if(FG==code)
  {
    while (wait (&status) != pid)
       /*spin fazer nada*/ ;
  }
  return;
}
