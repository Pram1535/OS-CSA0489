#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex;
int count = 1;
int max_count = 10;

void *print_odd(void *arg) {
    while (count <= max_count) {
        pthread_mutex_lock(&mutex);
        if (count % 2 != 0) {
            printf("Odd: %d\n", count++);
        }
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

void *print_even(void *arg) {
    while (count <= max_count) {
        pthread_mutex_lock(&mutex);
        if (count % 2 == 0) {
            printf("Even: %d\n", count++);
        }
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t odd_thread, even_thread;
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&odd_thread, NULL, print_odd, NULL);
    pthread_create(&even_thread, NULL, print_even, NULL);
    pthread_join(odd_thread, NULL);
    pthread_join(even_thread, NULL);
    pthread_mutex_destroy(&mutex);

    return 0;
}

