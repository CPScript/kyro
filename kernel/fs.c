#include "fs.h"
#include <stdio.h>
#include <string.h>

bool create_file(const char *name) {
    if (file_count >= MAX_FILES) {
        printf("File limit reached.\n");
        return false;
    }
    if (strlen(name) == 0) {
        printf("Filename cannot be empty.\n");
        return false;
    }
    if (strlen(name) >= FILENAME_LENGTH) {
        printf("Filename too long.\n");
        return false;
    }
    strcpy(file_list[file_count].name, name);
    file_list[file_count].is_directory = false;
    file_list[file_count].content[0] = '\0'; // Initialize content
    file_count++;
    return true;
}
