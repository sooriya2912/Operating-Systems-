#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 256 // Size of each block
#define NUM_BLOCKS 10  // Number of blocks in the file

// Function to write data to a specific block
void write_block(FILE *file, int block_index, const char *data) {
    fseek(file, block_index * BLOCK_SIZE, SEEK_SET);
    fwrite(data, sizeof(char), BLOCK_SIZE, file);
}

// Function to read data from a specific block
void read_block(FILE *file, int block_index) {
    char buffer[BLOCK_SIZE + 1];
    fseek(file, block_index * BLOCK_SIZE, SEEK_SET);
    fread(buffer, sizeof(char), BLOCK_SIZE, file);
    buffer[BLOCK_SIZE] = '\0'; // Ensure null termination
    printf("Block %d: %s\n", block_index, buffer);
}

int main() {
    FILE *file;
    int num_blocks;
    char data[BLOCK_SIZE];
    int index_block[NUM_BLOCKS];

    // Open file in read/write mode
    file = fopen("indexed_file.dat", "w+");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Initialize index block to point to each block
    for (int i = 0; i < NUM_BLOCKS; i++) {
        index_block[i] = i;
    }

    // Input number of blocks to write (up to NUM_BLOCKS)
    printf("Enter the number of blocks to write (max %d): ", NUM_BLOCKS);
    scanf("%d", &num_blocks);
    getchar(); // Consume newline left by scanf

    if (num_blocks > NUM_BLOCKS) {
        printf("Number of blocks exceeds maximum allowed (%d).\n", NUM_BLOCKS);
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // Write data to each block as specified
    for (int i = 0; i < num_blocks; i++) {
        printf("Enter data for block %d: ", i);
        fgets(data, BLOCK_SIZE, stdin);
        write_block(file, index_block[i], data);
    }

    // Read all blocks
    printf("\nReading all blocks:\n");
    for (int i = 0; i < num_blocks; i++) {
        read_block(file, index_block[i]);
    }

    // Close the file
    fclose(file);

    return 0;
}
