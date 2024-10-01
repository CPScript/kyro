#ifndef TTYENT_H
#define TTYENT_H

#include <stdbool.h>

struct ttyent {
    char *ty_name;
    char *ty_getty;
    char *ty_type;
};

#endif
