#ifndef WORD_EXP_H
#define WORD_EXP_H

#include <stdbool.h>

struct wordexp {
    int we_wordc;
    char **we_wordv;
    size_t we_offs;
};

#endif
