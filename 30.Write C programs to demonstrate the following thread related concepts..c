#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Define a thread function
void *thread_function(void *arg) {
    int thread_id = *((int *)arg);
    printf("Thread %d is running.\n", thread_id);
    sleep(1); // Simulate some work
    printf("Thread %d is exiting.\n", thread_id);
    pthread_exit(NULL); // Exit the thread
}

int main() {
    pthread_t thread1, thread2;
    int thread1_id = 1, thread2_id = 2;
    int res;

    // (i) Create threads
    res = pthread_create(&thread1, NULL, thread_function, (void *)&thread1_id);
    if (res) {
        fprintf(stderr, "Error creating thread 1: %d\n", res);
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&thread2, NULL, thread_function, (void *)&thread2_id);
    if (res) {
        fprintf(stderr, "Error creating thread 2: %d\n", res);
        exit(EXIT_FAILURE);
    }

    // (ii) Join threads
    res = pthread_join(thread1, NULL);
    if (res) {
        fprintf(stderr, "Error joining thread 1: %d\n", res);
        exit(EXIT_FAILURE);
    }

    res = pthread_join(thread2, NULL);
    if (res) {
        fprintf(stderr, "Error joining thread 2: %d\n", res);
        exit(EXIT_FAILURE);
    }

    // (iii) Check thread equality
    if (pthread_equal(thread1, thread2)) {
        printf("Thread 1 and Thread 2 are equal.\n");
    } else {
        printf("Thread 1 and Thread 2 are not equal.\n");
    }

    // (iv) Exit main thread
    printf("Main thread is exiting.\n");
    pthread_exit(NULL); // Main thread exits

    return 0;
}
