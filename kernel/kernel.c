#include "kernel.h"
#include "drivers/keyboard.h"
#include "drivers/mouse.h"
#include "drivers/network.h"
#include "fs/fs.h"
#include "terminal/terminal.h"
#include "user/user.h"
#include "networking.h"

void clear_screen() {
    char *video_memory = (char *)0xb8000;
    for (int i = 0; i < 80 * 25; i++) {
        video_memory[i * 2] = ' ';
        video_memory[i * 2 + 1] = 0x07;
    }
}

void print_message(const char *message) {
    char *video_memory = (char *)0xb8000;
    int offset = 0;
    while (*message) {
        video_memory[offset * 2] = *message;
        video_memory[offset * 2 + 1] = 0x07;
        offset++;
        message++;
    }
}

void kernel_init() {
    init_users();
    init_file_system();
    printf("Initialization complete. You can now boot the OS.\n");
}

void kernel_main() {
    clear_screen();
    print_message("Welcome to kyro OS!\nYour in control!");
    keyboard_init();
    mouse_init();
    start_tor(); // Start Tor during initialization
    network_init();
    fs_init();
    terminal_init();
    user_init();
    kernel_init(); // Initialize user accounts and file system
    login_prompt(); // Prompt for user login
    run_terminal(); // Start the terminal

    while (1) {}
}
