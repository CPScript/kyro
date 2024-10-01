#include "terminal.h"
#include <stdio.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100

void execute_command(const char *command) {
    if (strcmp(command, "exit") == 0) {
        print_message("Exiting...");
        // Handle exit logic
    } else if (strcmp(command, "help") == 0) {
        print_message("Available commands: help, exit, ls, cat <filename>");
    } else if (strncmp(command, "cat ", 4) == 0) {
        char *filename = command + 4;
        read_file(filename); // Call the read file function
    } else if (strcmp(command, "ls") == 0) {
        print_message("List of files: file1.txt, file2.txt");
    } else {
        print_message("Unknown command.");
    }
}

void run_terminal() {
    char command[MAX_COMMAND_LENGTH];
    
    while (1) {
        print_message("Enter command: ");
        gets(command); // Note: this is unsafe, needs better input handling
        execute_command(command);
    }
}
