#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMORY_SIZE 1000
#define NUM_BLOCKS 10

typedef struct {
    int size;
    int is_free;
} MemoryBlock;

MemoryBlock memory[NUM_BLOCKS];
void initialize_memory() {
    for (int i = 0; i < NUM_BLOCKS; i++) {
        memory[i].size = rand() % (MEMORY_SIZE / NUM_BLOCKS) + 1;
        memory[i].is_free = 1;
    }
}
void print_memory() {
    printf("Memory Blocks Status:\n");
    for (int i = 0; i < NUM_BLOCKS; i++) {
        printf("Block %d: Size = %d, %s\n", i, memory[i].size, memory[i].is_free ? "Free" : "Allocated");
    }
    printf("\n");
}
int first_fit(int size) {
    for (int i = 0; i < NUM_BLOCKS; i++) {
        if (memory[i].is_free && memory[i].size >= size) {
            memory[i].is_free = 0;
            return i;
        }
    }
    return -1; 
}
int best_fit(int size) {
    int best_index = -1;
    int best_size = MEMORY_SIZE + 1;

    for (int i = 0; i < NUM_BLOCKS; i++) {
        if (memory[i].is_free && memory[i].size >= size && memory[i].size < best_size) {
            best_index = i;
            best_size = memory[i].size;
        }
    }

    if (best_index != -1) {
        memory[best_index].is_free = 0;
    }
    return best_index;  // Allocation failed
}

// Worst-Fit Memory Allocation
int worst_fit(int size) {
    int worst_index = -1;
    int worst_size = -1;

    for (int i = 0; i < NUM_BLOCKS; i++) {
        if (memory[i].is_free && memory[i].size >= size && memory[i].size > worst_size) {
            worst_index = i;
            worst_size = memory[i].size;
        }
    }

    if (worst_index != -1) {
        memory[worst_index].is_free = 0;
    }
    return worst_index;  // Allocation failed
}

// Free a memory block
void free_block(int index) {
    if (index >= 0 && index < NUM_BLOCKS) {
        memory[index].is_free = 1;
    }
}

int main() {
    srand(time(NULL));  // Seed the random number generator
    initialize_memory();
    print_memory();

    // Test First-Fit allocation
    int size = 50;
    printf("Allocating %d bytes using First-Fit strategy.\n", size);
    int index = first_fit(size);
    if (index != -1) {
        printf("Allocated at block index %d.\n", index);
    } else {
        printf("Allocation failed.\n");
    }
    print_memory();

    // Test Best-Fit allocation
    size = 30;
    printf("Allocating %d bytes using Best-Fit strategy.\n", size);
    index = best_fit(size);
    if (index != -1) {
        printf("Allocated at block index %d.\n", index);
    } else {
        printf("Allocation failed.\n");
    }
    print_memory();

    // Test Worst-Fit allocation
    size = 70;
    printf("Allocating %d bytes using Worst-Fit strategy.\n", size);
    index = worst_fit(size);
    if (index != -1) {
        printf("Allocated at block index %d.\n", index);
    } else {
        printf("Allocation failed.\n");
    }
    print_memory();

    // Free the allocated blocks
    free_block(index);
    print_memory();

    return 0;
}
