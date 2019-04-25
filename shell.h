#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>

int parse(char *buf, char **args);

void execute(int numargs, char **args);

int builtin (char **args);

int socp(int, int);

/* constantes que podem tornar uteis*/

#define BG 0
#define FG 1
