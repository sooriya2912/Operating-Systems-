#include <stdio.h>
#include <stdlib.h>

#define MAX_RECORDS 100
#define RECORD_SIZE 256

// Function to write a record to the file
void write_record(FILE *file, int record_number, const char *data) {
    fseek(file, record_number * RECORD_SIZE, SEEK_SET);
    fwrite(data, sizeof(char), RECORD_SIZE, file);
}

// Function to read a record from the file
void read_record(FILE *file, int record_number) {
    char buffer[RECORD_SIZE];
    fseek(file, record_number * RECORD_SIZE, SEEK_SET);
    fread(buffer, sizeof(char), RECORD_SIZE, file);
    buffer[RECORD_SIZE - 1] = '\0'; // Ensure null termination
    printf("Record %d: %s\n", record_number, buffer);
}

int main() {
    FILE *file;
    char data[RECORD_SIZE];
    int num_records, record_number;

    // Open file in read/write mode
    file = fopen("sequential_file.dat", "w+");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Input number of records
    printf("Enter the number of records to write: ");
    scanf("%d", &num_records);
    getchar(); // Consume newline left by scanf

    // Write records to the file
    for (int i = 0; i < num_records; i++) {
        printf("Enter data for record %d: ", i);
        fgets(data, RECORD_SIZE, stdin);
        write_record(file, i, data);
    }

    // Read all records
    printf("\nReading all records:\n");
    for (int i = 0; i < num_records; i++) {
        read_record(file, i);
    }

    // Close the file
    fclose(file);

    return 0;
}
