#ifndef DIRENT_H
#define DIRENT_H

#include <stdbool.h>

struct dirent {
    int d_ino;
    int d_off;
    int d_reclen;
    int d_type;
    char d_name[256];
};

DIR *opendir(const char *name);
struct dirent *readdir(DIR *dirp);
int closedir(DIR *dirp);

#endif
