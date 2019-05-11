#include "shell.h"

/*
    parse . particiona o comando Unix (armazenado em buf) em argumentos
*/

int parse (char *buf, char **args)
{
  int cnt=0;  /* inicializa o número de argumentos */
  while ('\0' != *buf)
  {
    /* strip whitespace. Usa um NULL para indicar que o argumento anterior e. o ultimo */
    while (isspace ((unsigned char) *buf))
	    *buf++ = '\0';

    *args++ = buf;		/* salvaguarda argumento */
    cnt++;            /* novo: incrementa o número de argumentos */

    while ((*buf != '\0') && (!isspace ((unsigned char) *buf)))	/* salta sobre o argumento */
	    buf++;
  }
  
  *args = (char *) NULL;	/* o ultimo argumento e. NULL */
  return cnt;
}