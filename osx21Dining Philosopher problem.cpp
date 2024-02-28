#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define LEFT (philosopher + 4) % NUM_PHILOSOPHERS
#define RIGHT (philosopher + 1) % NUM_PHILOSOPHERS

sem_t mutex;
sem_t forks[NUM_PHILOSOPHERS];
int state[NUM_PHILOSOPHERS];

void test(int philosopher) {
    if (state[philosopher] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        state[philosopher] = EATING;
        printf("Philosopher %d is eating\n", philosopher);
        sleep(2); // Eating time
        printf("Philosopher %d finished eating\n", philosopher);
        sem_post(&forks[philosopher]);
    }
}

void take_forks(int philosopher) {
    sem_wait(&mutex);
    state[philosopher] = HUNGRY;
    printf("Philosopher %d is hungry\n", philosopher);
    test(philosopher);
    sem_post(&mutex);
    sem_wait(&forks[philosopher]);
}

void put_forks(int philosopher) {
    sem_wait(&mutex);
    state[philosopher] = THINKING;
    printf("Philosopher %d is thinking\n", philosopher);
    test(LEFT);
    test(RIGHT);
    sem_post(&mutex);
}

void* philosopher_actions(void* philosopher_ptr) {
    int philosopher = *((int*)philosopher_ptr);
    while (1) {
        sleep(1); // Thinking time
        take_forks(philosopher);
        sleep(1); // Eating time
        put_forks(philosopher);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];
    
    sem_init(&mutex, 0, 1);
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        sem_init(&forks[i], 0, 0);
        ids[i] = i;
    }
    
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        pthread_create(&philosophers[i], NULL, philosopher_actions, &ids[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        pthread_join(philosophers[i], NULL);
    }

    sem_destroy(&mutex);
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        sem_destroy(&forks[i]);
    }

    return 0;
}

