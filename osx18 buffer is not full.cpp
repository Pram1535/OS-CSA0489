#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 3

// Define a structure to represent the buffer
typedef struct {
    int buffer[BUFFER_SIZE];
    int in; // Index for inserting items
    int out; // Index for consuming items
    int count; // Number of items in the buffer
    pthread_mutex_t mutex; // Mutex for accessing buffer
    pthread_cond_t notEmpty; // Condition variable for buffer not empty
    pthread_cond_t notFull; // Condition variable for buffer not full
} Buffer;

// Function to initialize the buffer
void initBuffer(Buffer *buffer) {
    buffer->in = 0;
    buffer->out = 0;
    buffer->count = 0;
    pthread_mutex_init(&buffer->mutex, NULL);
    pthread_cond_init(&buffer->notEmpty, NULL);
    pthread_cond_init(&buffer->notFull, NULL);
}

// Function to produce an item and add it to the buffer
void produce(Buffer *buffer, int item) {
    pthread_mutex_lock(&buffer->mutex);
    while (buffer->count == BUFFER_SIZE) {
        printf("Buffer is full. Producer waits.\n");
        pthread_cond_wait(&buffer->notFull, &buffer->mutex);
    }
    buffer->buffer[buffer->in] = item;
    buffer->in = (buffer->in + 1) % BUFFER_SIZE;
    buffer->count++;
    printf("Produced item %d\n", item);
    if (buffer->count == 1) {
        pthread_cond_signal(&buffer->notEmpty);
    }
    pthread_mutex_unlock(&buffer->mutex);
}

// Function to consume an item from the buffer
int consume(Buffer *buffer) {
    pthread_mutex_lock(&buffer->mutex);
    while (buffer->count == 0) {
        printf("Buffer is empty. Consumer waits.\n");
        pthread_cond_wait(&buffer->notEmpty, &buffer->mutex);
    }
    int item = buffer->buffer[buffer->out];
    buffer->out = (buffer->out + 1) % BUFFER_SIZE;
    buffer->count--;
    printf("Consumed item %d\n", item);
    if (buffer->count == BUFFER_SIZE - 1) {
        pthread_cond_signal(&buffer->notFull);
    }
    pthread_mutex_unlock(&buffer->mutex);
    return item;
}

// Function to produce multiple items
void *producer(void *arg) {
    Buffer *buffer = (Buffer *)arg;
    for (int i = 1; i <= 4; ++i) {
        produce(buffer, i);
    }
    pthread_exit(NULL);
}

// Function to consume an item
void *consumer(void *arg) {
    Buffer *buffer = (Buffer *)arg;
    consume(buffer); // Consume an item at the beginning
    pthread_exit(NULL);
}

int main() {
    Buffer buffer;
    initBuffer(&buffer);

    pthread_t producerThread, consumerThread;
    pthread_create(&producerThread, NULL, producer, (void *)&buffer);
    pthread_create(&consumerThread, NULL, consumer, (void *)&buffer);

    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    return 0;
}

