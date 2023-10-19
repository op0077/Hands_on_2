#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
    //using fcntl
	int p_fd[2];
	int k =pipe(p_fd);

	if(k == -1){
		perror("pipe creation failed");
        return 0;
	}
    int pid = fork();
	if(pid)
	{
        //parent
		close(1); 
		close(p_fd[0]);   
		fcntl(p_fd[1],F_DUPFD,1);  
		execlp("ls", "ls", "-l", (char*) NULL);
	} 
	else
	{
        //child
		close(0);
		close(p_fd[1]);
		fcntl(p_fd[0],F_DUPFD,0);  
		execlp("wc", "wc", (char*) NULL);
	}
}