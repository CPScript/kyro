#include "user.h"
#include "fs.h"
#include <stdio.h>
#include <string.h>

// Function to process commands
void process_command(const char *command) {
    if (strncmp(command, "adduser ", 8) == 0) {
        char username[USERNAME_LENGTH];
        char password[PASSWORD_LENGTH];
        sscanf(command + 8, "%s %s", username, password);
        add_user(username, password, false); // Regular user
    } else if (strncmp(command, "login ", 6) == 0) {
        char username[USERNAME_LENGTH];
        char password[PASSWORD_LENGTH];
        sscanf(command + 6, "%s %s", username, password);
        if (authenticate(username, password)) {
            printf("Login successful!\n");
        } else {
            printf("Login failed.\n");
        }
    } else if (strncmp(command, "create ", 7) == 0) {
        char filename[FILENAME_LENGTH];
        sscanf(command + 7, "%s", filename);
        create_file(filename);
    } else if (strncmp(command, "mkdir ", 6) == 0) {
        char dirname[FILENAME_LENGTH];
        sscanf(command + 6, "%s", dirname);
        create_directory(dirname);
    } else if (strncmp(command, "rmdir ", 6) == 0) {
        char dirname[FILENAME_LENGTH];
        sscanf(command + 6, "%s", dirname);
        delete_directory(dirname);
    } else if (strncmp(command, "delete ", 7) == 0) {
        char filename[FILENAME_LENGTH];
        sscanf(command + 7, "%s", filename);
        delete_file(filename);
    } else if (strncmp(command, "cat ", 4) == 0) {
        char filename[FILENAME_LENGTH];
        sscanf(command + 4, "%s", filename);
        read_file(filename);
    } else if (strcmp(command, "ls") == 0) {
        list_files();
    } else if (strcmp(command, "help") == 0) {
        printf("Available commands: adduser, login, create, mkdir, rmdir, delete, cat, ls, help\n");
    } else {
        printf("Unknown command.\n");
    }
}
