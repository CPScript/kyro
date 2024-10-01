#include "stdio.h"
#include "fs.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#define EOF (-1)

FILE *fopen(const char *filename, const char *mode) {
    if (strcmp(mode, "r") != 0) {
        return NULL; // Only support read mode for now
    }

    for (int i = 0; i < file_count; i++) {
        if (strcmp(file_list[i].name, filename) == 0) {
            FILE *fp = (FILE *)malloc(sizeof(FILE));
            fp->fd = i; // Use the index as the file descriptor
            fp->buffer = file_list[i].content;
            fp->buffer_size = strlen(file_list[i].content);
            fp->buffer_index = 0;
            return fp;
        }
    }

    return NULL; // File not found
}

int fclose(FILE *fp) {
    free(fp);
    return 0;
}

char *fgets(char *str, int num, FILE *fp) {
    if (!fp || fp->buffer_index >= fp->buffer_size) {
        return NULL;
    }

    int i;
    for (i = 0; i < num - 1 && fp->buffer_index < fp->buffer_size; i++) {
        char c = fp->buffer[fp->buffer_index++];
        str[i] = c;
        if (c == '\n') {
            i++;
            break;
        }
    }
    str[i] = '\0';
    return str;
}

int printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    char buffer[1024];
    vsnprintf(buffer, 1024, format, args);
    va_end(args);
    print_message(buffer);
    return 0;
}
