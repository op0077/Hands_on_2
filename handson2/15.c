#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
int main()
{
    int p_fd[2];
    pid_t pid;
    pipe(p_fd);
    pid=fork();
	if(pid==-1)
	{
        perror("fork error");
        return 0; // exit with error
    }
    if(!pid)
    {
        //child
        close(p_fd[1]); //close write end
        char op[30];
        int data = read(p_fd[0],op,sizeof(op));
        printf("Data read by child from parent: %s\n",op);
        close(p_fd[0]);
    }
    else
    {   
        //parent
        close(p_fd[0]); // close read end
        char op[] =  "hello";
        write(p_fd[1],op,sizeof(op));
        printf("data send from parent : %s\n",op);
        close(p_fd[1]);
    }
}
/*compile and run*/
