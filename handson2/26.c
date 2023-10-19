#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msgbuf {
    long mtype;     // Message type(greater than 0) to distinguish among different messages in same queue
    char mtext[100]; 
};

int main() {
    int msqid;
    key_t key;
    struct msgbuf message;

    key = ftok(".", 'Z'); 

    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    msqid = msgget(key, 0666 | IPC_CREAT);

    if (msqid == -1) {
        perror("msgget");
        exit(1);
    }

    // Prepare the message
    message.mtype = 1; // Message type (greater than 0)
    strcpy(message.mtext, "Hello, Message");

    // Send the message to the queue
    if (msgsnd(msqid, &message, sizeof(message.mtext), 0) == -1) {
        perror("msgsnd");
        exit(1);
    }
    printf("Message %s",message.mtext);


    return 0;
}