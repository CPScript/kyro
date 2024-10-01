#include "os.h"
#include "user.h"
#include "fs.h"
#include "terminal.h"

void clear_screen() {
    char *video_memory = (char *)0xb8000;
    for (int i = 0; i < 80 * 25; i++) {
        video_memory[i * 2] = ' ';
        video_memory[i * 2 + 1] = 0x07;
    }
}

void main() {
    clear_screen();
    print_message("Welcome! enjoy!");
    init_users(); // Initialize user-accounts
    init_file_system(); // Initialize file-system
    run_terminal(); // Start terminal

    while (1) {} // Keep running
}
