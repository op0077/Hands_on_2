#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

int main() {
    key_t key;
    int msqid;

    // Generate a unique key using ftok
    // ftok  -  convert  a pathname and a project identifier to a System V IPC key
    if ((key = ftok(".", 'Z')) == -1)
     {
        perror("ftok");
    }

    // Create a message queue with the generated key
    if ((msqid = msgget(key, IPC_CREAT | 0764)) == -1) {
        perror("error in creating Message Queue");
    }

    printf("Message Queue Key: 0x%x\n", key);
    printf("Message Queue ID: %d\n", msqid);

    return 0;
}