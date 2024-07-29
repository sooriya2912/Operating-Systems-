#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

sem_t forks[NUM_PHILOSOPHERS];
pthread_t philosophers[NUM_PHILOSOPHERS];

void *philosopher(void *num) {
    int id = *(int *)num;
    int left_fork = id;
    int right_fork = (id + 1) % NUM_PHILOSOPHERS;

    while (1) {
        printf("Philosopher %d is thinking.\n", id);
        sleep(1); 
        printf("Philosopher %d is hungry.\n", id);
        sem_wait(&forks[left_fork]);
        printf("Philosopher %d picked up fork %d (left fork).\n", id, left_fork);
        sem_wait(&forks[right_fork]);
        printf("Philosopher %d picked up fork %d (right fork).\n", id, right_fork);
        printf("Philosopher %d is eating.\n", id);
        sleep(1); 
        sem_post(&forks[right_fork]);
        printf("Philosopher %d put down fork %d (right fork).\n", id, right_fork);
        sem_post(&forks[left_fork]);
        printf("Philosopher %d put down fork %d (left fork).\n", id, left_fork);
    }
}

int main() {
    int ids[NUM_PHILOSOPHERS];
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&forks[i], 0, 1);
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Wait for philosopher threads to finish
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy semaphores
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&forks[i]);
    }

    return 0;
}
