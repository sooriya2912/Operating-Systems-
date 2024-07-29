#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "employees.dat"
#define MAX_NAME_LENGTH 50

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    int age;
    float salary;
} Employee;

// Function to create a new employee record
void create_employee() {
    FILE *file = fopen(FILENAME, "ab");  // Open file in append-binary mode
    if (!file) {
        perror("Failed to open file");
        return;
    }

    Employee emp;
    printf("Enter Employee ID: ");
    scanf("%d", &emp.id);
    printf("Enter Employee Name: ");
    scanf(" %[^\n]", emp.name);
    printf("Enter Employee Age: ");
    scanf("%d", &emp.age);
    printf("Enter Employee Salary: ");
    scanf("%f", &emp.salary);

    fwrite(&emp, sizeof(Employee), 1, file);

    fclose(file);
    printf("Employee record added successfully.\n");
}

// Function to read all employee records
void read_employees() {
    FILE *file = fopen(FILENAME, "rb");  // Open file in read-binary mode
    if (!file) {
        perror("Failed to open file");
        return;
    }

    Employee emp;
    while (fread(&emp, sizeof(Employee), 1, file)) {
        printf("ID: %d\n", emp.id);
        printf("Name: %s\n", emp.name);
        printf("Age: %d\n", emp.age);
        printf("Salary: %.2f\n", emp.salary);
        printf("-------------------------\n");
    }

    fclose(file);
}

// Function to update an existing employee record by ID
void update_employee() {
    FILE *file = fopen(FILENAME, "r+b");  // Open file in read-write-binary mode
    if (!file) {
        perror("Failed to open file");
        return;
    }

    int id;
    printf("Enter Employee ID to update: ");
    scanf("%d", &id);

    Employee emp;
    int found = 0;
    while (fread(&emp, sizeof(Employee), 1, file)) {
        if (emp.id == id) {
            found = 1;
            fseek(file, -sizeof(Employee), SEEK_CUR);  // Move file pointer back to record start

            printf("Enter new Employee Name: ");
            scanf(" %[^\n]", emp.name);
            printf("Enter new Employee Age: ");
            scanf("%d", &emp.age);
            printf("Enter new Employee Salary: ");
            scanf("%f", &emp.salary);

            fwrite(&emp, sizeof(Employee), 1, file);
            printf("Employee record updated successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Employee with ID %d not found.\n", id);
    }

    fclose(file);
}

// Function to delete an employee record by ID
void delete_employee() {
    FILE *file = fopen(FILENAME, "rb");  // Open file in read-binary mode
    if (!file) {
        perror("Failed to open file");
        return;
    }

    FILE *temp_file = fopen("temp.dat", "wb");  // Temporary file to store non-deleted records
    if (!temp_file) {
        perror("Failed to open temporary file");
        fclose(file);
        return;
    }

    int id;
    printf("Enter Employee ID to delete: ");
    scanf("%d", &id);

    Employee emp;
    int found = 0;
    while (fread(&emp, sizeof(Employee), 1, file)) {
        if (emp.id != id) {
            fwrite(&emp, sizeof(Employee), 1, temp_file);
        } else {
            found = 1;
        }
    }

    if (found) {
        printf("Employee with ID %d deleted successfully.\n", id);
    } else {
        printf("Employee with ID %d not found.\n", id);
    }

    fclose(file);
    fclose(temp_file);
    remove(FILENAME);  // Remove the original file
    rename("temp.dat", FILENAME);  // Rename temp file to original file
}

int main() {
    int choice;

    while (1) {
        printf("\nEmployee Record System\n");
        printf("1. Add Employee\n");
        printf("2. List Employees\n");
        printf("3. Update Employee\n");
        printf("4. Delete Employee\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                create_employee();
                break;
            case 2:
                read_employees();
                break;
            case 3:
                update_employee();
                break;
            case 4:
                delete_employee();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
