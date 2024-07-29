#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>

void list_directory(const char *path) {
    DIR *dir;
    struct dirent *entry;

    // Open the directory
    dir = opendir(path);
    if (dir == NULL) {
        perror("Error opening directory");
        exit(EXIT_FAILURE);
    }

    // Read and print the contents of the directory
    printf("Contents of %s:\n", path);
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    // Close the directory
    if (closedir(dir) == -1) {
        perror("Error closing directory");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    // Determine the directory to list
    const char *path = (argc > 1) ? argv[1] : ".";

    list_directory(path);

    return 0;
}
