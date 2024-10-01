#ifndef STDIO_H
#define STDIO_H

#include <stdarg.h>
#include <stdbool.h>

typedef struct {
    int fd; // File descriptor
    char *buffer; // Buffer for reading/writing
    int buffer_size; // Size of the buffer
    int buffer_index; // Current position in the buffer
} FILE;

FILE *fopen(const char *filename, const char *mode);
int fclose(FILE *fp);
char *fgets(char *str, int num, FILE *fp);
int printf(const char *format, ...);

#endif // STDIO_H
