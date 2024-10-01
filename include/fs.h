#ifndef FS_H
#define FS_H

#include <stdbool.h>

#define MAX_FILES 100
#define FILENAME_LENGTH 50

typedef struct {
    char name[FILENAME_LENGTH];
    bool is_directory; // Flag to indicate if it's a directory
    // will add more file attributes later (like permissions, size, etc.)
} File;

File file_list[MAX_FILES]; // Array to store files
int file_count = 0;         // Count of registered files

bool create_file(const char *name, bool is_directory);
bool delete_file(const char *name);
void list_files();

#endif // FS_H
