#ifndef FCNTL_H
#define FCNTL_H

#include <stdbool.h>

int open(const char *pathname, int flags, mode_t mode);
int close(int fd);

#endif
