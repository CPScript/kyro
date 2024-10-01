#include "fs.h"
#include <stdio.h>
#include <string.h>

bool create_file(const char *name) {
    if (file_count >= MAX_FILES) {
        printf("File limit reached.\n");
        return false;
    }
    strcpy(file_list[file_count].name, name);
    file_list[file_count].is_directory = false;
    file_list[file_count].content[0] = '\0'; // Initialize content
    file_count++;
    return true;
}

bool create_directory(const char *name) {
    return create_file(name); // Treat directory like a file for simplicity
}

bool delete_file(const char *name) {
    for (int i = 0; i < file_count; i++) {
        if (strcmp(file_list[i].name, name) == 0 && !file_list[i].is_directory) {
            for (int j = i; j < file_count - 1; j++) {
                file_list[j] = file_list[j + 1]; // Shift files left
            }
            file_count--;
            return true; // File deleted
        }
    }
    return false; // File not found
}

bool delete_directory(const char *name) {
    return delete_file(name); // Treat directory like a file for simplicity
}

bool read_file(const char *name) {
    for (int i = 0; i < file_count; i++) {
        if (strcmp(file_list[i].name, name) == 0 && !file_list[i].is_directory) {
            printf("Contents of %s:\n%s\n", file_list[i].name, file_list[i].content);
            return true;
        }
    }
    return false; // File not found
}

void list_files() {
    for (int i = 0; i < file_count; i++) {
        printf("%s%s\n", file_list[i].name, file_list[i].is_directory ? "/" : "");
    }
}
