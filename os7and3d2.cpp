#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    int shmid;
    key_t key;
    char *shared_memory;
    const char *message = "Hello, shared memory!";

    key = ftok("progfile", 65);
    shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    shared_memory = shmat(shmid, NULL, 0);
    sprintf(shared_memory, "%s", message);
    printf("Data written to shared memory: %s\n", shared_memory);

    shmdt(shared_memory);

    return 0;
}

