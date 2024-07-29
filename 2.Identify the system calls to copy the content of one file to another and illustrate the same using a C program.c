#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main() {
    char source_file[256];
    char dest_file[256];

    printf("Enter the source file name: ");
    scanf("%255s", source_file);

    printf("Enter the destination file name: ");
    scanf("%255s", dest_file);

    int source_fd, dest_fd;
    ssize_t nread;
    char buffer[BUFFER_SIZE];

    source_fd = open(source_file, O_RDONLY);
    if (source_fd < 0) {
        perror("Error opening source file");
        return 1;
    }

    dest_fd = open(dest_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd < 0) {
        perror("Error opening/creating destination file");
        close(source_fd);
        return 1;
    }

    while ((nread = read(source_fd, buffer, BUFFER_SIZE)) > 0) {
        if (write(dest_fd, buffer, nread) != nread) {
            perror("Error writing to destination file");
            close(source_fd);
            close(dest_fd);
            return 1;
        }
    }

    if (nread < 0) {
        perror("Error reading from source file");
    }

    close(source_fd);
    close(dest_fd);

    return 0;
}
