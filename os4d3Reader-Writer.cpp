#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_READERS 5
#define NUM_WRITERS 2

int shared_resource = 0, readers_count = 0;
sem_t mutex, rw_mutex;

void *reader(void *arg) {
    int reader_id = *((int *)arg);
    while (1) {
        sem_wait(&mutex);
        if (++readers_count == 1) sem_wait(&rw_mutex);
        sem_post(&mutex);

        printf("Reader %d reads: %d\n", reader_id, shared_resource);

        sem_wait(&mutex);
        if (--readers_count == 0) sem_post(&rw_mutex);
        sem_post(&mutex);

        usleep(rand() % 1000000);
    }
}

void *writer(void *arg) {
    int writer_id = *((int *)arg);
    while (1) {
        sem_wait(&rw_mutex);
        shared_resource++;
        printf("Writer %d writes: %d\n", writer_id, shared_resource);
        sem_post(&rw_mutex);
        usleep(rand() % 1000000);
    }
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int i, reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];

    sem_init(&mutex, 0, 1);
    sem_init(&rw_mutex, 0, 1);

    for (i = 0; i < NUM_READERS; ++i) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    for (i = 0; i < NUM_WRITERS; ++i) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    for (i = 0; i < NUM_READERS; ++i) pthread_join(readers[i], NULL);
    for (i = 0; i < NUM_WRITERS; ++i) pthread_join(writers[i], NULL);

    sem_destroy(&mutex);
    sem_destroy(&rw_mutex);

    return 0;
}

