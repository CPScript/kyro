#include "kernel.h"
#include "drivers/keyboard.h"
#include "drivers/mouse.h"
#include "drivers/network.h"
#include "fs.h"
#include "terminal.h"
#include "user.h"
#include "shell.h"
#include "package_manager.h"
#include "scripting.h"

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
    print_message("Welcome to Kyro OS!\nYour in control!");
    keyboard_init();
    mouse_init();
    network_init();
    fs_init();
    terminal_init();
    user_init();
    shell_init();
    package_manager_init();
    scripting_init();
    kernel_init();
    login_prompt();
    run_terminal();
    run_shell();
    while (1) {}
}
