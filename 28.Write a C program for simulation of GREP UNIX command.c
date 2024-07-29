#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void grep(const char *pattern, FILE *file) {
    char buffer[BUFFER_SIZE];

    // Read file line by line
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // Check if the pattern is in the current line
        if (strstr(buffer, pattern) != NULL) {
            printf("%s", buffer);
        }
    }
}

int main(int argc, char *argv[]) {
    FILE *file;
    const char *pattern;
    const char *filename;

    // Check if enough arguments are provided
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <pattern> <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pattern = argv[1];
    filename = argv[2];

    // Open the file
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Call the grep function to search for the pattern
    grep(pattern, file);

    // Close the file
    if (fclose(file) == EOF) {
        perror("Error closing file");
        exit(EXIT_FAILURE);
    }

    return 0;
}
