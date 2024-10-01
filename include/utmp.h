#ifndef UTM_H
#define UTM_H

#include <stdbool.h>

struct utmp {
    short ut_type;
    pid_t ut_pid;
    char ut_line[8];
    char ut_id[4];
    char ut_user[32];
    char ut_host[256];
    struct timeval ut_tv;
    int ut_session;
    struct timeval ut_sys_tv;
    int ut_sys_session;
};

#endif
