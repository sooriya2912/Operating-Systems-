#include <stdio.h>
#include <stdlib.h>

// Structure to represent a block of memory
struct Block {
    int size;
    int isAllocated;
    int processId;
};

// Function to find the first fit block for a given process size
int findFirstFitBlock(struct Block memoryBlocks[], int numBlocks, int processSize) {
    for (int i = 0; i < numBlocks; i++) {
        if (!memoryBlocks[i].isAllocated && memoryBlocks[i].size >= processSize) {
            return i;
        }
    }
    return -1;
}

// Function to allocate memory using the first fit algorithm
void allocateMemory(struct Block memoryBlocks[], int numBlocks, int processSize, int processId) {
    int blockIndex = findFirstFitBlock(memoryBlocks, numBlocks, processSize);
    if (blockIndex != -1) {
        memoryBlocks[blockIndex].isAllocated = 1;
        memoryBlocks[blockIndex].processId = processId;
        printf("Process %d allocated to block of size %d\n", processId, memoryBlocks[blockIndex].size);
    } else {
        printf("Process %d cannot be allocated memory\n", processId);
    }
}

// Function to deallocate memory for a given process
void deallocateMemory(struct Block memoryBlocks[], int numBlocks, int processId) {
    for (int i = 0; i < numBlocks; i++) {
        if (memoryBlocks[i].isAllocated && memoryBlocks[i].processId == processId) {
            memoryBlocks[i].isAllocated = 0;
            printf("Process %d deallocated from block of size %d\n", processId, memoryBlocks[i].size);
            return;
        }
    }
    printf("Process %d not found\n", processId);
}

// Function to print the current state of memory blocks
void printMemoryBlocks(struct Block memoryBlocks[], int numBlocks) {
    printf("\nMemory Blocks:\n");
    for (int i = 0; i < numBlocks; i++) {
        printf("Block %d: Size: %d, Allocated: %d, Process ID: %d\n",
               i, memoryBlocks[i].size, memoryBlocks[i].isAllocated, memoryBlocks[i].processId);
    }
    printf("\n");
}

int main() {
    // Define memory blocks
    struct Block memoryBlocks[] = {
        {100, 0, -1},
        {500, 0, -1},
        {200, 0, -1},
        {300, 0, -1},
        {600, 0, -1}
    };
    int numBlocks = sizeof(memoryBlocks) / sizeof(memoryBlocks[0]);

    printMemoryBlocks(memoryBlocks, numBlocks);

    // Allocate memory for processes
    allocateMemory(memoryBlocks, numBlocks, 212, 1);
    allocateMemory(memoryBlocks, numBlocks, 417, 2);
    allocateMemory(memoryBlocks, numBlocks, 112, 3);
    allocateMemory(memoryBlocks, numBlocks, 426, 4);

    printMemoryBlocks(memoryBlocks, numBlocks);

    // Deallocate memory for a process
    deallocateMemory(memoryBlocks, numBlocks, 2);

    printMemoryBlocks(memoryBlocks, numBlocks);

    // Allocate memory for another process
    allocateMemory(memoryBlocks, numBlocks, 426, 5);

    printMemoryBlocks(memoryBlocks, numBlocks);

    return 0;
}
