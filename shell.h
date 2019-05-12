#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>

int parse(char *buf, char **args);

void execute(int numargs, char **args);

int builtin (char **args, int numargs);

int socp(int, int);

int redirects (int numargs, char* args[]);

void calc(char* value1, char* op, char* value2);

void bits (char* op1, char* op, char* op2);

int isjpg (int fileDescriptor);

void aviso (char* mesg, int tempo);

void* avisowrapper(void* args);

void* avisowrapperEs(void* args);

void* socpth(void* args);

/* constantes que podem ser uteis*/
#define BG 0
#define FG 1

/* estrutura para passar os argumentos no aviso */
typedef struct 
{
    char msg[100];
    int tempo;
}aviso_t;

/* cópia de ficheiro em baixo nível com threads */
typedef struct
{
    int in;
    int out;
}copiar_t;