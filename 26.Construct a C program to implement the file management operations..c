#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>  // Ensure this header is included for S_IRUSR, S_IWUSR

#define BUFFER_SIZE 100

int main() {
    int fd;
    ssize_t bytesWritten, bytesRead;
    char buffer[BUFFER_SIZE];

    // 1. Create and open a file for writing
    fd = open("example_file.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    // 2. Write data to the file
    const char *data = "Hello, this is a test message for file management operations.\n";
    bytesWritten = write(fd, data, strlen(data));
    if (bytesWritten == -1) {
        perror("Error writing to file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // 3. Close the file
    if (close(fd) == -1) {
        perror("Error closing file after writing");
        exit(EXIT_FAILURE);
    }

    // 4. Reopen the file for reading
    fd = open("example_file.txt", O_RDONLY);
    if (fd == -1) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }

    // 5. Read data from the file
    bytesRead = read(fd, buffer, BUFFER_SIZE - 1);
    if (bytesRead == -1) {
        perror("Error reading file");
        close(fd);
        exit(EXIT_FAILURE);
    }
    buffer[bytesRead] = '\0'; // Null-terminate the buffer

    // Print the read data
    printf("Read from file: %s", buffer);

    // 6. Close the file after reading
    if (close(fd) == -1) {
        perror("Error closing file after reading");
        exit(EXIT_FAILURE);
    }

    // 7. Delete the file
    if (unlink("example_file.txt") == -1) {
        perror("Error deleting file");
        exit(EXIT_FAILURE);
    }

    return 0;
}
