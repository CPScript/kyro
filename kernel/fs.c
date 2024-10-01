#include "fs.h"
#include <string.h>

#define MAX_FILES 10
#define FILENAME_LEN 20

typedef struct {
    char name[FILENAME_LEN];
    char content[100]; // Simple file content
} File;

File files[MAX_FILES];
int file_count = 0;

void init_file_system() {
    // Initialize with some dummy files
    strcpy(files[file_count].name, "file1.txt");
    strcpy(files[file_count++].content, "This is file 1 content.");
    
    strcpy(files[file_count].name, "file2.txt");
    strcpy(files[file_count++].content, "This is file 2 content.");
}

File* find_file(const char *filename) {
    for (int i = 0; i < file_count; i++) {
        if (strcmp(files[i].name, filename) == 0) {
            return &files[i];
        }
    }
    return NULL;
}

void read_file(const char *filename) {
    File *file = find_file(filename);
    if (file) {
        print_message(file->content);
    } else {
        print_message("File not found.");
    }
}
