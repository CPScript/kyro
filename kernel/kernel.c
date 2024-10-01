#include "os.h"
#include "user.h"
#include "fs.h"
#include "terminal.h"
#include "networking.h"

void clear_screen() {
    char *video_memory = (char *)0xb8000;
    for (int i = 0; i < 80 * 25; i++) {
        video_memory[i * 2] = ' ';
        video_memory[i * 2 + 1] = 0x07;
    }
}

void _start() {
    clear_screen();
    print_message("Welcome to Privacy OS!");
    start_tor(); // Start Tor during initialization
    init_users(); // Initialize user accounts
    login_prompt(); // Prompt for user login
    init_file_system(); // Initialize file system
    run_terminal(); // Start the terminal

    while (1) {}
}
