// ramfs.c

#include <linux/fs.h>

void init_ramfs(void) {
    // Initialize the RAM-based file system
    // Create the root directory
    mkdir("/");

    // Create the /bin directory
    mkdir("/bin");

    // Create the /dev directory
    mkdir("/dev");

    // Create the /etc directory
    mkdir("/etc");

    // Create the /home directory
    mkdir("/home");

    // Create the /lib directory
    mkdir("/lib");

    // Create the /proc directory
    mkdir("/proc");

    // Create the /sbin directory
    mkdir("/sbin");

    // Create the /sys directory
    mkdir("/sys");

    // Create the /tmp directory
    mkdir("/tmp");

    // Create the /usr directory
    mkdir("/usr");

    // Create the /var directory
    mkdir("/var");
}
