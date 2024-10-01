#ifndef TERMIOS_H
#define TERMIOS_H

#include <stdbool.h>

struct termios {
    int c_iflag;
    int c_oflag;
    int c_cflag;
    int c_lflag;
    int c_line;
    int c_cc[20];
};

int tcgetattr(int fd, struct termios *termios_p);
int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);

#endif
