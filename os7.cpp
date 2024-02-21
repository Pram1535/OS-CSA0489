#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>

int main() { 
    int i; 
    void *shared_memory; 
    char buff[100]; 
    int shmid; 
    
    // Create or access the shared memory segment
    shmid = shmget((key_t)2345, 1024, 0666 | IPC_CREAT); 
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    printf("Key of shared memory is %d\n", shmid); 
    
    // Attach the shared memory segment to the process
    shared_memory = shmat(shmid, NULL, 0); 
    if (shared_memory == (void *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }
    printf("Process attached at %p\n", shared_memory); 
    
    // Write data to shared memory
    printf("Enter some data to write to shared memory\n"); 
    read(STDIN_FILENO, buff, 100); 
    strcpy(shared_memory, buff); 
    
    printf("You wrote : %s\n", (char *)shared_memory); 
    
    // Detach the shared memory segment from the process
    if (shmdt(shared_memory) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }
    
    return 0;
}

