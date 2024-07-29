#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 10
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2

// Shared buffer and related variables
int buffer[BUFFER_SIZE];
int in = 0;  // Index for the producer
int out = 0; // Index for the consumer

// Semaphores and mutex
sem_t empty;   // Number of empty slots
sem_t full;    // Number of full slots
pthread_mutex_t mutex;  // Mutex for buffer access

void *producer(void *arg) {
    int item;
    while (1) {
        item = rand() % 100; // Produce an item
        sem_wait(&empty);   // Wait for an empty slot
        pthread_mutex_lock(&mutex); // Lock the buffer

        // Add item to buffer
        buffer[in] = item;
        printf("Producer %ld produced %d at index %d\n", (long)arg, item, in);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex); // Unlock the buffer
        sem_post(&full);   // Signal that a new item is available

        sleep(rand() % 3); // Sleep for a while
    }
    return NULL;
}

void *consumer(void *arg) {
    int item;
    while (1) {
        sem_wait(&full);    // Wait for a full slot
        pthread_mutex_lock(&mutex); // Lock the buffer

        // Remove item from buffer
        item = buffer[out];
        printf("Consumer %ld consumed %d from index %d\n", (long)arg, item, out);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex); // Unlock the buffer
        sem_post(&empty);   // Signal that a new slot is available

        sleep(rand() % 3); // Sleep for a while
    }
    return NULL;
}

int main() {
    pthread_t producers[NUM_PRODUCERS];
    pthread_t consumers[NUM_CONSUMERS];

    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE); // Buffer starts empty
    sem_init(&full, 0, 0);            // No items in buffer initially
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    for (long i = 0; i < NUM_PRODUCERS; i++) {
        pthread_create(&producers[i], NULL, producer, (void *)i);
    }
    for (long i = 0; i < NUM_CONSUMERS; i++) {
        pthread_create(&consumers[i], NULL, consumer, (void *)i);
    }

    // Wait for threads to complete (they actually won't in this infinite loop example)
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producers[i], NULL);
    }
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumers[i], NULL);
    }

    // Clean up
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
