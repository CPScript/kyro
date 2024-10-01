#ifndef FS_H
#define FS_H

#include <stdbool.h>
#include <string.h>

#define MAX_FILES 5000
#define FILENAME_LENGTH 50
#define FILE_CONTENT_LENGTH 256

typedef struct {
    char name[FILENAME_LENGTH];
    char content[FILE_CONTENT_LENGTH];
    bool is_directory;
} File;

File file_list[MAX_FILES];
int file_count;

bool create_file(const char *name, bool is_directory);
bool delete_file(const char *name);
bool delete_directory(const char *name);
void list_files();
bool read_file(const char *name);

#endif
