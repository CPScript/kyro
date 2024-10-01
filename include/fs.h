#ifndef FS_H
#define FS_H

#include <stdbool.h>
#include <string.h>

#define MAX_FILES 5000
#define FILENAME_LENGTH 50
#define FILE_CONTENT_LENGTH 256

typedef struct {
    char name[FILENAME_LENGTH];
    char content[FILE_CONTENT_LENGTH]; // Add content field
    bool is_directory; // Flag to indicate if it's a directory
} File;

File file_list[MAX_FILES]; // Array to store files
int file_count;            // Count of registered files

bool create_file(const char *name);
bool create_directory(const char *name);
bool delete_file(const char *name);
bool delete_directory(const char *name);
void list_files();
bool read_file(const char *name);

#endif
