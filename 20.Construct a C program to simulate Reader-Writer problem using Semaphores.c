#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 2

sem_t rw_mutex; // Semaphore for reader-writer mutual exclusion
sem_t mutex; // Semaphore for read count update mutual exclusion
int read_count = 0; // Number of readers currently accessing the resource

void* reader(void* arg) {
    int reader_id = *((int*)arg);
    while (1) {
        // Reader section
        sem_wait(&mutex);
        read_count++;
        if (read_count == 1) {
            sem_wait(&rw_mutex); // First reader locks the writer out
        }
        sem_post(&mutex);

        // Reading section
        printf("Reader %d is reading\n", reader_id);
        sleep(rand() % 3); // Simulate reading time

        // Reader section
        sem_wait(&mutex);
        read_count--;
        if (read_count == 0) {
            sem_post(&rw_mutex); // Last reader releases the writer lock
        }
        sem_post(&mutex);

        sleep(rand() % 3); // Simulate time between reads
    }
}

void* writer(void* arg) {
    int writer_id = *((int*)arg);
    while (1) {
        // Writing section
        sem_wait(&rw_mutex); // Writer locks the resource
        printf("Writer %d is writing\n", writer_id);
        sleep(rand() % 3); // Simulate writing time
        sem_post(&rw_mutex); // Writer releases the resource

        sleep(rand() % 3); // Simulate time between writes
    }
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];

    sem_init(&rw_mutex, 0, 1); // Initialize rw_mutex semaphore
    sem_init(&mutex, 0, 1); // Initialize mutex semaphore

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        if (pthread_create(&readers[i], NULL, reader, &reader_ids[i]) != 0) {
            fprintf(stderr, "Error creating reader thread\n");
            return 1;
        }
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        if (pthread_create(&writers[i], NULL, writer, &writer_ids[i]) != 0) {
            fprintf(stderr, "Error creating writer thread\n");
            return 1;
        }
    }

    // Join reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        if (pthread_join(readers[i], NULL) != 0) {
            fprintf(stderr, "Error joining reader thread\n");
            return 1;
        }
    }

    // Join writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        if (pthread_join(writers[i], NULL) != 0) {
            fprintf(stderr, "Error joining writer thread\n");
            return 1;
        }
    }

    // Destroy semaphores
    sem_destroy(&rw_mutex);
    sem_destroy(&mutex);

    return 0;
}
