#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define SHARED_MEMORY_INITIAL_VALUE 10

// Shared memory (global variable)
int sharedMemory = SHARED_MEMORY_INITIAL_VALUE;

// Semaphore declaration
sem_t semaphore;

// Function to create threads
void* threadFunction(void* arg) {
    int* multiplier = (int*)arg;
    
    // Wait on semaphore
    sem_wait(&semaphore);

    // Critical section - accessing shared memory
    sharedMemory *= *multiplier;
    printf("Thread ID: %ld, Updated Shared Memory: %d\n", pthread_self(), sharedMemory);

    // Signal semaphore
    sem_post(&semaphore);

    pthread_exit(NULL);
}

int main() {
    // Initialize semaphore
    sem_init(&semaphore, 0, 1); // Initial value of semaphore is 1

    pthread_t thread1, thread2;

    // Create thread 1 (double the shared memory value)
    int multiplier1 = 2;
    pthread_create(&thread1, NULL, threadFunction, (void*)&multiplier1);

    // Create thread 2 (five times the shared memory value)
    int multiplier2 = 5;
    pthread_create(&thread2, NULL, threadFunction, (void*)&multiplier2);

    // Join threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destroy semaphore
    sem_destroy(&semaphore);

    return 0;
}

