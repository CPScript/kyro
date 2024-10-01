#include "terminal.h"
#include <stdio.h>

void run_terminal() {
    char command[100];
    
    while (1) {
        print_message("Enter command: ");
        // Simple input mechanism (to be replaced with a proper one)
        gets(command);
        
        if (strcmp(command, "exit") == 0) {
            break;
        } else {
            print_message("Unknown command");
        }
    }
}
