#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key;
    int msgid;
    struct msg_buffer message;

    key = ftok("progfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);

    message.msg_type = 1;
    printf("Enter message to send: ");
    fgets(message.msg_text, 100, stdin);
    msgsnd(msgid, &message, sizeof(message), 0);

    msgrcv(msgid, &message, sizeof(message), 1, 0);
    printf("Received message: %s", message.msg_text);

    msgctl(msgid, IPC_RMID, NULL);
    
    return 0;
}

