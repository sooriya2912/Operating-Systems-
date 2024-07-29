#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 256 // Size of each block
#define MAX_BLOCKS 10  // Number of blocks in the file system

// Define a structure for a block
typedef struct Block {
    char data[BLOCK_SIZE];
    struct Block *next;
} Block;

// Function to create a new block
Block *create_block(const char *data, Block *next) {
    Block *new_block = (Block *)malloc(sizeof(Block));
    if (new_block == NULL) {
        perror("Error allocating memory for block");
        exit(EXIT_FAILURE);
    }
    strncpy(new_block->data, data, BLOCK_SIZE - 1);
    new_block->data[BLOCK_SIZE - 1] = '\0'; // Ensure null termination
    new_block->next = next;
    return new_block;
}

// Function to write data to a file (linked list)
void write_file(Block **head, Block **tail, const char *data) {
    Block *new_block = create_block(data, NULL);
    if (*tail != NULL) {
        (*tail)->next = new_block;
    } else {
        *head = new_block;
    }
    *tail = new_block;
}

// Function to read data from a file (linked list)
void read_file(Block *head) {
    Block *current = head;
    int block_index = 0;
    while (current != NULL) {
        printf("Block %d: %s\n", block_index++, current->data);
        current = current->next;
    }
}

int main() {
    Block *head = NULL; // Pointer to the first block of the file
    Block *tail = NULL; // Pointer to the last block of the file

    char data[BLOCK_SIZE];
    int num_blocks;

    // Input number of blocks
    printf("Enter the number of blocks to write (max %d): ", MAX_BLOCKS);
    scanf("%d", &num_blocks);
    getchar(); // Consume newline left by scanf

    if (num_blocks > MAX_BLOCKS) {
        printf("Number of blocks exceeds maximum allowed (%d).\n", MAX_BLOCKS);
        exit(EXIT_FAILURE);
    }

    // Write data to each block
    for (int i = 0; i < num_blocks; i++) {
        printf("Enter data for block %d: ", i);
        fgets(data, BLOCK_SIZE, stdin);
        data[strcspn(data, "\n")] = '\0'; // Remove newline character
        write_file(&head, &tail, data);
    }

    // Read all blocks
    printf("\nReading all blocks:\n");
    read_file(head);

    // Free allocated memory
    Block *current = head;
    Block *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    return 0;
}
