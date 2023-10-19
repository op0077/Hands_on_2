#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int p_fd[2];
    int k =pipe(p_fd);

	if(k == -1){
		perror("pipe creation failed");
        exit(1);
	}

    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(1);
    }

    if (pid == 0)
    {
        // Child process
        close(p_fd[0]); 
        dup2(p_fd[1], 1); 
        close(p_fd[1]); 

        // execute "ls -l"
        execlp("ls", "ls", "-l", NULL);
        perror("execlp ls");
        exit(1);
    } 
    else 
    {
        // parent
        close(p_fd[1]); 
        dup2(p_fd[0], STDIN_FILENO); 
        close(p_fd[0]); 

        int grep_fd[2];
        if (pipe(grep_fd) == -1) 
        {
            perror("pipe");
            exit(1);
        }

        pid_t grep_pid = fork();
        if (grep_pid == -1) 
        {
            perror("fork");
            exit(1);
        }

        if (!grep_pid) 
        {
            // child
            close(grep_fd[0]);
            dup2(grep_fd[1], STDOUT_FILENO); 
            close(grep_fd[1]); 

            execlp("grep", "grep", "^d", NULL);
            perror("execlp grep");
            exit(1);
        } 
        else 
        {
            // parent
            close(grep_fd[1]); 
            dup2(grep_fd[0], STDIN_FILENO); 
            close(grep_fd[0]); 

            execlp("wc", "wc", NULL);
            perror("execlp wc");
            exit(1);
        }
    }

    return 0;
}