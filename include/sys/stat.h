#ifndef SYS_STAT_H
#define SYS_STAT_H

#include <stdbool.h>

struct stat {
    int st_mode;
    int st_ino;
    int st_dev;
    int st_nlink;
    int st_uid;
    int st_gid;
    int st_rdev;
    int st_size;
    int st_blksize;
    int st_blocks;
    int st_atime;
    int st_mtime;
    int st_ctime;
};

int stat(const char *pathname, struct stat *buf);

#endif
