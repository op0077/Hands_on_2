#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msgbuf {
    long mtype;     // message type(greater than 0) to distinguish among different messages in same queue
    char mtext[100]; 
};

int main() {
    int msqid;
    key_t key;
    struct msgbuf msg;

    key = ftok("/tmp", 'A'); 

    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    msqid = msgget(key, 0666 | IPC_CREAT);

    if (msqid == -1) {
        perror("msgget");
        exit(1);
    }

    // prepare the msg
    msg.mtype = 1; 
    strcpy(msg.mtext, "Hello, msg");

    // send the msg to the queue
    if (msgsnd(msqid, &msg, sizeof(msg.mtext), 0) == -1) {
        perror("msgsnd");
        exit(1);
    }
    printf("msg %s",msg.mtext);


    return 0;
}