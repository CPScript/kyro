#ifndef NETINET_IP_ICMP_H
#define NETINET_IP_ICMP_H

#include <stdbool.h>

struct icmp {
    unsigned char icmp_type;
    unsigned char icmp_code;
    unsigned short icmp_cksum;
    unsigned short icmp_id;
    unsigned short icmp_seq;
};

#endif
