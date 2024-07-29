#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

// Function to compare two integers (for qsort)
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Function to calculate the total seek time for SCAN scheduling
int calculate_seek_time(int requests[], int num_requests, int start_position, int disk_size, int direction) {
    int seek_time = 0;
    int current_position = start_position;
    
    // Sort requests for SCAN algorithm
    qsort(requests, num_requests, sizeof(int), compare);
    
    // Find the position of the start_position in the sorted array
    int i;
    for (i = 0; i < num_requests; i++) {
        if (requests[i] >= start_position) break;
    }

    // Scan in the direction
    if (direction == 1) { // Right
        // Serve requests from start_position to the end of the disk
        for (int j = i; j < num_requests; j++) {
            seek_time += abs(requests[j] - current_position);
            current_position = requests[j];
        }
        // Move to the end of the disk if not already there
        if (current_position < disk_size - 1) {
            seek_time += abs(disk_size - 1 - current_position);
            current_position = disk_size - 1;
        }
        // Serve requests from the beginning of the disk to the start_position
        for (int j = 0; j < i; j++) {
            seek_time += abs(requests[j] - current_position);
            current_position = requests[j];
        }
    } else { // Left
        // Serve requests from start_position to the beginning of the disk
        for (int j = i - 1; j >= 0; j--) {
            seek_time += abs(requests[j] - current_position);
            current_position = requests[j];
        }
        // Move to the beginning of the disk if not already there
        if (current_position > 0) {
            seek_time += abs(current_position);
            current_position = 0;
        }
        // Serve requests from the end of the disk to the start_position
        for (int j = num_requests - 1; j >= i; j--) {
            seek_time += abs(requests[j] - current_position);
            current_position = requests[j];
        }
    }

    return seek_time;
}

int main() {
    int requests[MAX_REQUESTS];
    int num_requests;
    int start_position;
    int disk_size;
    int direction;

    // Input number of requests
    printf("Enter the number of disk requests (max %d): ", MAX_REQUESTS);
    scanf("%d", &num_requests);

    if (num_requests > MAX_REQUESTS) {
        printf("Number of requests exceeds maximum allowed (%d).\n", MAX_REQUESTS);
        exit(EXIT_FAILURE);
    }

    // Input the disk size
    printf("Enter the size of the disk: ");
    scanf("%d", &disk_size);

    // Input the starting position of the disk head
    printf("Enter the starting position of the disk head: ");
    scanf("%d", &start_position);

    // Input disk requests
    printf("Enter the disk requests:\n");
    for (int i = 0; i < num_requests; i++) {
        printf("Request %d: ", i + 1);
        scanf("%d", &requests[i]);
    }

    // Input the direction of movement (1 for right, 0 for left)
    printf("Enter the direction of movement (1 for right, 0 for left): ");
    scanf("%d", &direction);

    if (direction != 0 && direction != 1) {
        printf("Invalid direction. Enter 1 for right or 0 for left.\n");
        exit(EXIT_FAILURE);
    }

    // Calculate and display the seek time
    int total_seek_time = calculate_seek_time(requests, num_requests, start_position, disk_size, direction);
    printf("\nDisk scheduling order (SCAN):\n");
    for (int i = 0; i < num_requests; i++) {
        printf("%d ", requests[i]);
    }
    printf("\nTotal seek time: %d\n", total_seek_time);

    return 0;
}
