#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

// Function to calculate total seek time for FCFS scheduling
int calculate_seek_time(int requests[], int num_requests, int start_position) {
    int seek_time = 0;
    int current_position = start_position;

    for (int i = 0; i < num_requests; i++) {
        seek_time += abs(requests[i] - current_position);
        current_position = requests[i];
    }

    return seek_time;
}

int main() {
    int requests[MAX_REQUESTS];
    int num_requests;
    int start_position;

    // Input number of requests
    printf("Enter the number of disk requests (max %d): ", MAX_REQUESTS);
    scanf("%d", &num_requests);

    if (num_requests > MAX_REQUESTS) {
        printf("Number of requests exceeds maximum allowed (%d).\n", MAX_REQUESTS);
        exit(EXIT_FAILURE);
    }

    // Input the starting position of the disk head
    printf("Enter the starting position of the disk head: ");
    scanf("%d", &start_position);

    // Input disk requests
    printf("Enter the disk requests:\n");
    for (int i = 0; i < num_requests; i++) {
        printf("Request %d: ", i + 1);
        scanf("%d", &requests[i]);
    }

    // Calculate and display the seek time
    int total_seek_time = calculate_seek_time(requests, num_requests, start_position);
    printf("\nDisk scheduling order (FCFS):\n");
    for (int i = 0; i < num_requests; i++) {
        printf("%d ", requests[i]);
    }
    printf("\nTotal seek time: %d\n", total_seek_time);

    return 0;
}
