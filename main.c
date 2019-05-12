#include "shell.h"

char prompt[100];

int main ()
{
  int len;
  char linha[1024];		/* um comando */
  char *args[64];		/* com um maximo de 64 argumentos */
  int numargs;

  strcpy (prompt, "SOSHELL: Introduza um comando : prompt>");

  while (1)
  {
    printf ("%s", prompt);

    if (fgets (linha, 1023, stdin) == NULL)
	  {
	    printf ("\n");
	    exit (0);
	  }
    len = strlen (linha);
    if (1 == len)
	    continue;		/* linha é apenas \n */
    if (linha[len - 1] == '\n')
	    linha[len - 1] = '\0';

    numargs=parse(linha, args);	/* particiona a string em argumentos */

    if (!builtin (args, numargs))
    	execute (numargs, args);		/* executa o comando */
  }
  execute(numargs, args);
  return 0;
}

int builtin (char **args, int numargs)
{
  if (strcmp (args[0], "sair") == 0)
  {
    exit (0);
    return 1;
  }
  if (strncmp (args[0], "42", 2) == 0)
  {
    printf ("42 is the answer to life the universe and everything\n");
    return 1;			/* funcionalidade embutida */
  }

// implementação da função embutido obterinfo
  if (0==strcmp(args[0], "obterinfo"))
  {
    printf("SoShell 2018 versao 1.0\n");
    return 1;   // comando embutido
  }

// implementaçaõ da função da mundança do prompt
  if (strlen(args[0])>4 && 0==strncmp(args[0], "PS1=", 4))
  {
    strcpy(prompt, args[0]+4);
    return 1;   // comando embutido
  }

// implementação da função builtin quemsoueu
  if (0==strncmp(args[0], "quemsoueu", 9))
  {
    system("id");
    return 1;   // comando embutido
  }

// implementação da função builtin para mundança de diretório (cd)
  if (0==strcmp(args[0], "cd"))
  {
    int err;
    if ((NULL==args[1]) || (0==strcmp(args[1], "~")))
      err=chdir(getenv("HOME"));
    else
      err=chdir(args[1]);

    if (err<0) perror ("chdir failed");

    return 1;
  }

// implementação do comando embutido socp
  if (0==strcmp(args[0], "socp"))
  {
    int fd=open(args[1], O_RDONLY);
    int fo=open(args[2], O_CREAT | O_WRONLY);
    socp(fd, fo);
    return 1;
  }

// implementação calculadora
  if (0==strcmp(args[0], "calc") && numargs==4)
  {
    calc(args[1], args[2], args[3]);
    return 1; // comando embutido
  }

// implementação da calculadora binária
  if (0==strcmp(args[0], "bits") && numargs==4)
  {
    bits(args[1], args[2], args[3]);
    return 1; // comando embutido
  }

// implementação da verificação de ficheiro isjpg
  if (0==strcmp(args[0], "isjpg") && (numargs==2))
  {
    printf("%d\n", isjpg(*args[1]));
    return 1;
  }

  // implementação aviso de teste
  if(strcmp(args[0], "avisoTeste")==0)
  {
    aviso(args[1], atoi(args[2]));
    return 1;
  }

  // implementação aviso com Threads
  if(strcmp(args[0], "aviso")==0)
  {
    pthread_t th;

    pthread_create(&th, NULL, avisowrapper, (void*)args);
    pthread_join(th, NULL);

    return 1;
  }

  // passar argumentos com estrutura
  if(strcmp(args[0], "avisoEs")==0)
  {
    pthread_t th;
    aviso_t* ptr = (aviso_t*)malloc(sizeof(aviso_t));

    strcpy(ptr->msg, args[1]);
    ptr->tempo=atoi(args[2]);

    pthread_create(&th, NULL, avisowrapperEs, (void*)ptr);
    pthread_join(th, NULL);

    return 1;
  }

  if(strcmp(args[0], "socpth")==0)
  {
    pthread_t th;
    copiar_t* ptr = (copiar_t*)malloc(sizeof(copiar_t));

    ptr->in=open(args[1], O_RDONLY);
    ptr->out=open(args[2], O_CREAT | O_WRONLY);

    pthread_create(&th, NULL, socpth, (void*)ptr);
    pthread_join(th, NULL);

    return 1;
  }  

/*
  if (strcmp (args[0], "qualquercoisa") == 0) 
  {
       funcionalidade();
       return 1;
  }

   if ( strcmp(args[0],"socp")==0) 
   {
     socp( args[1], args[2]);
     return 1;
   }
*/

/* 0 para indicar que não existe comando embutido */

  return 0;
}