#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>  // Include this header for S_IRUSR and S_IWUSR

#define BUFFER_SIZE 100

int main() {
    int fd;
    ssize_t bytesRead, bytesWritten;
    char buffer[BUFFER_SIZE];

    // 1. Create and open a file
    fd = open("example.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    // 2. Write data to the file
    const char *data = "Hello, this is a test message.\n";
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

    // 4. Open the file for reading
    fd = open("example.txt", O_RDONLY);
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
    buffer[bytesRead] = '\0';

    // Print the read data
    printf("Read from file: %s", buffer);

    // 6. Reposition the file offset
    if (lseek(fd, 0, SEEK_SET) == -1) {
        perror("Error seeking in file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // 7. Read data again to demonstrate repositioning
    bytesRead = read(fd, buffer, BUFFER_SIZE - 1);
    if (bytesRead == -1) {
        perror("Error reading file");
        close(fd);
        exit(EXIT_FAILURE);
    }
    buffer[bytesRead] = '\0';
    printf("Read from file again: %s", buffer);

    // 8. Close the file
    if (close(fd) == -1) {
        perror("Error closing file after reading");
        exit(EXIT_FAILURE);
    }

    // 9. Delete the file
    if (unlink("example.txt") == -1) {
        perror("Error deleting file");
        exit(EXIT_FAILURE);
    }

    return 0;
}
