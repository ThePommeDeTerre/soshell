#include "shell.h"

void calc(char* value1, char* op, char* value2) 
{
    double result;

    switch(*op)
    {
        case '+' :
            result=atof(value1) + atof(value2);   break;
        
        case '-' :
            result=atof(value1) - atof(value2);   break;

        case '/' :
            if(*value2 == 0)    perror(NULL);
            result=atof(value1) / atof(value2);   break;
        
        case '*' :
            result=atof(value1) * atof(value2);   break;

        case '^' :
            result=powf((atof(value1)), (atof(value2)));

        default:
            break;
    }
    printf("%f\n", result);
}

void bits (char* op1, char* op, char* op2)
{
    int result;

    switch(*op)
    {
        case '&' :
            result=atoi(op1) & atoi(op2);    break;

        case '^' :
            result=atoi(op1) ^ atoi(op2); break;

        case '|' :
            result=atoi(op1) | atoi(op2);    break;
        
        default:
            break;
    }
    printf("%d\n", result);
}

int isjpg (int fileDescriptor)
{
    unsigned char b[4];
    read(fileDescriptor, b, 4);

    // voltar ao início do ficheiro com lseek
    lseek(fileDescriptor, 0, SEEK_SET);

    if(b[0]==0xff && b[1]==0xd8 && b[2]==0xff && b[3]==0xe0) return 1;
    
    return 0;
}