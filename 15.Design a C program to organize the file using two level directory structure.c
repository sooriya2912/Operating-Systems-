#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 5
#define MAX_FILES 10
#define MAX_FILENAME_LENGTH 50
#define MAX_USERNAME_LENGTH 50

typedef struct {
    char name[MAX_FILENAME_LENGTH];
    int is_used;
} File;

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    File files[MAX_FILES];
} UserDirectory;

UserDirectory directories[MAX_USERS];

void initialize_directories() {
    for (int i = 0; i < MAX_USERS; i++) {
        strcpy(directories[i].username, "");
        for (int j = 0; j < MAX_FILES; j++) {
            directories[i].files[j].is_used = 0;
        }
    }
}

int find_user(char *username) {
    for (int i = 0; i < MAX_USERS; i++) {
        if (strcmp(directories[i].username, username) == 0) {
            return i;
        }
    }
    return -1;
}

int add_user(char *username) {
    for (int i = 0; i < MAX_USERS; i++) {
        if (strcmp(directories[i].username, "") == 0) {
            strcpy(directories[i].username, username);
            return i;
        }
    }
    return -1; // No space for new user
}

void create_file(char *username, char *filename) {
    int user_index = find_user(username);
    if (user_index == -1) {
        user_index = add_user(username);
        if (user_index == -1) {
            printf("No space for new user.\n");
            return;
        }
    }
    
    for (int i = 0; i < MAX_FILES; i++) {
        if (directories[user_index].files[i].is_used && strcmp(directories[user_index].files[i].name, filename) == 0) {
            printf("File %s already exists in user %s's directory.\n", filename, username);
            return;
        }
    }
    
    for (int i = 0; i < MAX_FILES; i++) {
        if (!directories[user_index].files[i].is_used) {
            strcpy(directories[user_index].files[i].name, filename);
            directories[user_index].files[i].is_used = 1;
            printf("File %s created in user %s's directory.\n", filename, username);
            return;
        }
    }
    printf("User %s's directory is full. Cannot create more files.\n", username);
}

void delete_file(char *username, char *filename) {
    int user_index = find_user(username);
    if (user_index == -1) {
        printf("User %s not found.\n", username);
        return;
    }
    
    for (int i = 0; i < MAX_FILES; i++) {
        if (directories[user_index].files[i].is_used && strcmp(directories[user_index].files[i].name, filename) == 0) {
            directories[user_index].files[i].is_used = 0;
            printf("File %s deleted from user %s's directory.\n", filename, username);
            return;
        }
    }
    printf("File %s not found in user %s's directory.\n", filename, username);
}

void list_files(char *username) {
    int user_index = find_user(username);
    if (user_index == -1) {
        printf("User %s not found.\n", username);
        return;
    }

    printf("Files in user %s's directory:\n", username);
    for (int i = 0; i < MAX_FILES; i++) {
        if (directories[user_index].files[i].is_used) {
            printf("%s\n", directories[user_index].files[i].name);
        }
    }
}

int main() {
    initialize_directories();
    
    int choice;
    char username[MAX_USERNAME_LENGTH];
    char filename[MAX_FILENAME_LENGTH];
    
    while (1) {
        printf("\nTwo-Level Directory System\n");
        printf("1. Create File\n");
        printf("2. Delete File\n");
        printf("3. List Files\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter username: ");
                scanf("%s", username);
                printf("Enter filename to create: ");
                scanf("%s", filename);
                create_file(username, filename);
                break;
            case 2:
                printf("Enter username: ");
                scanf("%s", username);
                printf("Enter filename to delete: ");
                scanf("%s", filename);
                delete_file(username, filename);
                break;
            case 3:
                printf("Enter username: ");
                scanf("%s", username);
                list_files(username);
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
