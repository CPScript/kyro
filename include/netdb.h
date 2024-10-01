#ifndef NETDB_H
#define NETDB_H

#include <stdbool.h>

struct hostent {
    char *h_name;
    char **h_aliases;
    int h_addrtype;
    int h_length;
    char **h_addr_list;
};

#endif
