#ifndef NETINET_UDP_H
#define NETINET_UDP_H

#include <stdbool.h>

struct udphdr {
    unsigned short uh_sport;
    unsigned short uh_dport;
    unsigned short uh_ulen;
    unsigned short uh_sum;
};

#endif
