#include "fs.h"
#include <stdio.h>
#include <string.h>

bool create_file(const char *name, bool is_directory) {
    if (file_count >= MAX_FILES) {
        printf("File limit reached.\nPlease clear some space\n");
        return false;
    }
    strcpy(file_list[file_count].name, name);
    file_list[file_count].is_directory = is_directory;
    file_count++;
    return true;
}

bool delete_file(const char *name) {
    for (int i = 0; i < file_count; i++) {
        if (strcmp(file_list[i].name, name) == 0) {
            for (int j = i; j < file_count - 1; j++) {
                file_list[j] = file_list[j + 1]; // Shift files left
            }
            file_count--;
            return true; // File deleted
        }
    }
    return false; // File not found
}

void list_files() {
    for (int i = 0; i < file_count; i++) {
        printf("%s%s\n", file_list[i].name, file_list[i].is_directory ? "/" : "");
    }
}
