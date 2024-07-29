#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define PRODUCERS 3
#define CONSUMERS 3

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t empty, full, mutex;

void* producer(void* arg) {
    int item;
    int producer_id = *((int*)arg);
    while (1) {
        item = rand() % 100; // Produce a random item
        sem_wait(&empty); // Decrement empty
        sem_wait(&mutex); // Enter critical section

        buffer[in] = item;
        printf("Producer %d produced item %d at index %d\n", producer_id, item, in);
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&mutex); // Leave critical section
        sem_post(&full); // Increment full

        sleep(rand() % 3); // Simulate production time
    }
}

void* consumer(void* arg) {
    int item;
    int consumer_id = *((int*)arg);
    while (1) {
        sem_wait(&full); // Decrement full
        sem_wait(&mutex); // Enter critical section

        item = buffer[out];
        printf("Consumer %d consumed item %d from index %d\n", consumer_id, item, out);
        out = (out + 1) % BUFFER_SIZE;

        sem_post(&mutex); // Leave critical section
        sem_post(&empty); // Increment empty

        sleep(rand() % 3); // Simulate consumption time
    }
}

int main() {
    pthread_t prod[PRODUCERS], cons[CONSUMERS];
    int prod_ids[PRODUCERS], cons_ids[CONSUMERS];

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    // Create producer threads
    for (int i = 0; i < PRODUCERS; i++) {
        prod_ids[i] = i + 1;
        pthread_create(&prod[i], NULL, producer, &prod_ids[i]);
    }

    // Create consumer threads
    for (int i = 0; i < CONSUMERS; i++) {
        cons_ids[i] = i + 1;
        pthread_create(&cons[i], NULL, consumer, &cons_ids[i]);
    }

    // Join producer threads
    for (int i = 0; i < PRODUCERS; i++) {
        pthread_join(prod[i], NULL);
    }

    // Join consumer threads
    for (int i = 0; i < CONSUMERS; i++) {
        pthread_join(cons[i], NULL);
    }

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
