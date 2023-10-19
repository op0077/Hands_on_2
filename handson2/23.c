#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main() {
    
    long number = sysconf(_SC_OPEN_MAX);
    //OPEN_MAX - _SC_OPEN_MAX The maximum number of files that a process can open at any time.
    if (number == -1) 
    {
        perror("error");
    }
    printf("maximum number of open files for this process: %ld\n", number);

    int fd[2];
    if (pipe(fd) == -1) 
    {
        perror("create pipe error");
    }

    long size = fcntl(fd[0], F_GETPIPE_SZ);
    
    printf("size of a pipe: %ld bytes\n", size);
    close(fd[0]);
    close(fd[1]);

    return 0;
}