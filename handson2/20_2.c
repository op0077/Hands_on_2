/*
============================================================================
Name : 20_2.c
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
    
    int fd = open(fifo1,O_RDONLY);
    if(fd==-1)
    {
        perror("open");
        return 0;
    }
    char buffer[256];
    ssize_t bytes_read;
    while(1)
    {
        memset(&buffer,0,sizeof(buffer));
        bytes_read = read(fd,&buffer,sizeof(buffer));
        printf("%s\n",buffer);
    }
    return 0;
}
/*compile and run*/