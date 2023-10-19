#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main() {
    int p_parent[2]; // Parent to Child
    int p_child[2]; // Child to Parent
    char msg[] = "msg from parent to child";
    char msg1[] = "msg from child to parent";
    char op[100];
    char op1[100];
    pid_t pid;

    // Create the pipes
    if (pipe(p_parent) == -1 || pipe(p_child) == -1) {
        perror("Pipe creation failed");
        return 0;
    }

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 0;
    }

    if (pid)
     { 
        // Parent process
        close(p_parent[0]); 
        close(p_child[1]); 

        write(p_parent[1], msg, sizeof(msg));
        read(p_child[0], op1, sizeof(op1));
        printf("parent : %s\n", op1);
        close(p_parent[1]);
        close(p_child[0]);
    } 
    else 
    { 
        // Child 
        close(p_parent[1]); 
        close(p_child[0]); 
        read(p_parent[0], op, sizeof(op));
        printf("child : %s\n", op);
        write(p_child[1], msg1, sizeof(msg1));

        close(p_parent[0]);
        close(p_child[1]);
    }

    return 0;
}