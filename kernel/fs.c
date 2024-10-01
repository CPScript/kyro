#include "fs.h"
#include <stdio.h>
#include <string.h>

#define MAX_FILE_NAME_LENGTH 50
#define MAX_FILE_CONTENT_LENGTH 256

typedef struct {
    char name[MAX_FILE_NAME_LENGTH];
    char content[MAX_FILE_CONTENT_LENGTH];
    bool is_directory;
} File;

File file_list[MAX_FILES];
int file_count = 0;

bool create_file(const char *name, bool is_directory) {
    if (file_count >= MAX_FILES) {
        printf("File limit reached.\n");
        return false;
    }
    if (strlen(name) == 0) {
        printf("Filename cannot be empty.\n");
        return false;
    }
    if (strlen(name) >= MAX_FILE_NAME_LENGTH) {
        printf("Filename too long.\n");
        return false;
    }
    strcpy(file_list[file_count].name, name);
    file_list[file_count].is_directory = is_directory;
    file_list[file_count].content[0] = '\0';
    file_count++;
    return true;
}

bool create_file_or_directory(const char *name, bool is_directory) {
    return create_file(name, is_directory);
}

bool delete_file(const char *name) {
    for (int i = 0; i < file_count; i++) {
        if (strcmp(file_list[i].name, name) == 0 && !file_list[i].is_directory) {
            for (int j = i; j < file_count - 1; j++) {
                file_list[j] = file_list[j + 1];
            }
            file_count--;
            return true;
        }
    }
    printf("File not found.\n");
    return false;
}

bool delete_directory(const char *name) {
    for (int i = 0; i < file_count; i++) {
        if (strcmp(file_list[i].name, name) == 0 && file_list[i].is_directory) {
            for (int j = i; j < file_count - 1; j++) {
                file_list[j] = file_list[j + 1];
            }
            file_count--;
            return true;
        }
    }
    printf("Directory not found.\n");
    return false;
}

void list_files() {
    printf("Files:\n");
    for (int i = 0; i < file_count; i++) {
        if (!file_list[i].is_directory) {
            printf("%s\n", file_list[i].name);
        }
    }
    printf("Directories:\n");
    for (int i = 0; i < file_count; i++) {
        if (file_list[i].is_directory) {
            printf("%s\n", file_list[i].name);
        }
    }
}

bool read_file(const char *name) {
    for (int i = 0; i < file_count; i++) {
        if (strcmp(file_list[i].name, name) == 0 && !file_list[i].is_directory) {
            printf("%s\n", file_list[i].content);
            return true;
        }
    }
    printf("File not found.\n");
    return false;
}
