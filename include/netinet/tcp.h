#ifndef NETINET_TCP_H
#define NETINET_TCP_H

#include <stdbool.h>

struct tcphdr {
    unsigned short th_sport;
    unsigned short th_dport;
    unsigned int th_seq;
    unsigned int th_ack;
    unsigned short th_x2;
    unsigned short th_flags;
    unsigned short th_win;
    unsigned short th_sum;
    unsigned short th_urp;
};

#endif
