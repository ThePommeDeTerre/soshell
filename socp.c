#include "shell.h"

int socp(int in, int out) {

    int n, size;

    size=lseek(in, 0, SEEK_END);
    
    char* buff=(char*)malloc(size);

    lseek(in, 0, SEEK_SET);

    while((n=read(in, buff, size))>0) {
        write(out, buff, n);
    }

    perror(NULL);

    return 0;
}
