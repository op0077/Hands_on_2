/*
============================================================================
Name : 20_1.c
Author : Harshilkumar Buha
Description : Write two programs so that both can communicate by FIFO -Use one way communication.
Date : 15th sep, 2023.
============================================================================
*/
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
int main()
{
    const char *fifo1 = "/tmp/myfifo1";
    // if(mkfifo(fifo1,0666)==-1)
    // {
    //     perror("mkfifo1");
    //     return 0;
    // }
    int fd = open(fifo1,O_RDWR);
    if(fd==-1)
    {
        perror("open");
        return 0;
    }
    char op[100];
    while(op!="exit")
    {
        char msg[]="User1 : ";
        scanf("%s",op);
        strcat(msg,op);
        if(write(fd,msg,strlen(msg))==-1)
        {
            perror("write");
            return 0;
        }
    }
    return 0;
}
/*compile and run*/