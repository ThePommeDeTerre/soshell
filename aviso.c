#include "shell.h"

void aviso (char* mesg, int tempo)
{
    while(tempo > 0)
    {
        sleep(1);
        tempo--;
    }
    fprintf(stderr, "Aviso : %s\n", mesg);
}

// aviso com thread ---> ERRADO
void* avisowrapper(void* args)
{
    char** argsin=(char**)args;
    aviso(argsin[1], atoi(argsin[2]));
    pthread_exit(NULL);
    return NULL;
}

// aviso com estrutura & thread
void* avisowrapperEs(void* args)
{
    aviso_t* ptr=(aviso_t*) args;
    aviso(ptr->msg, ptr->tempo);
    free(ptr);
    pthread_exit(NULL);
    return NULL;
}