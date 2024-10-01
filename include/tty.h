#ifndef TTY_H
#define TTY_H

#include <stdbool.h>

#define TTY_NAME_MAX 32

struct tty {
    char name[TTY_NAME_MAX];
    int fd;
};

#endif
