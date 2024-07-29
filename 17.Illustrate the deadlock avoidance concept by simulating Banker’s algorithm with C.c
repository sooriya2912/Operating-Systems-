#include <stdio.h>
#include <stdbool.h>

#define P 3 // Number of processes
#define R 3 // Number of resource types

// Function to check if a process can be allocated the requested resources
bool canAllocate(int process, int need[P][R], int available[R]) {
    for (int i = 0; i < R; i++) {
        if (need[process][i] > available[i]) {
            return false;
        }
    }
    return true;
}

// Banker's Algorithm for Deadlock Avoidance
bool bankersAlgorithm(int allocation[P][R], int max[P][R], int available[R]) {
    int need[P][R];
    bool finished[P] = {0};
    int safeSequence[P];
    int work[R];
    
    // Calculate the need matrix
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    
    // Initialize work with available resources
    for (int i = 0; i < R; i++) {
        work[i] = available[i];
    }
    
    int count = 0;
    while (count < P) {
        bool found = false;
        
        for (int p = 0; p < P; p++) {
            if (!finished[p] && canAllocate(p, need, work)) {
                // If a process can be allocated, add its resources to work
                for (int k = 0; k < R; k++) {
                    work[k] += allocation[p][k];
                }
                
                // Add this process to the safe sequence
                safeSequence[count++] = p;
                finished[p] = true;
                found = true;
            }
        }
        
        if (!found) {
            // If no process can be allocated, then system is not in a safe state
            printf("System is not in a safe state.\n");
            return false;
        }
    }
    
    // Print the safe sequence
    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < P; i++) {
        printf("P%d ", safeSequence[i]);
    }
    printf("\n");
    
    return true;
}

int main() {
    int allocation[P][R] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2}
    };
    
    int max[P][R] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2}
    };
    
    int available[R] = {3, 3, 2};
    
    bankersAlgorithm(allocation, max, available);
    
    return 0;
}
