#ifndef NETINET_IP_H
#define NETINET_IP_H

#include <stdbool.h>

struct iphdr {
    unsigned int ihl;
    unsigned int version;
    unsigned int tos;
    unsigned short tot_len;
    unsigned short id;
    unsigned short frag_off;
    unsigned char ttl;
    unsigned char protocol;
    unsigned short check;
    unsigned int saddr;
    unsigned int daddr;
};

#endif
