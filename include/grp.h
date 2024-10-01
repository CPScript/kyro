#ifndef GRP_H
#define GRP_H

#include <stdbool.h>

struct group {
    char *gr_name;
    char *gr_passwd;
    gid_t gr_gid;
    char **gr_mem;
};

#endif
