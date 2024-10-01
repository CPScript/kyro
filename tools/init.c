#include <stdio.h>
#include <stdlib.h>
#include "user.h"
#include "fs.h"

// Function prototypes
void init_users();
void init_file_system();

void init_users() {
    add_user("admin", "adminpass", true); // Example of an admin user
    add_user("user1", "user1pass", false); // Example of a regular user
    printf("User system initialized with %d users.\n", user_count);
}

void init_file_system() {
    // Optionally, you could create some default files or directories
    create_directory("home");
    create_file("readme.txt");
    strcpy(file_list[0].content, "Welcome to the OS!\n");
    printf("File system initialized with %d files.\n", file_count);
}

int main() {
    init_users();

    init_file_system();

    printf("Initialization complete. You can now boot the OS.\n");

    return 0;
}
