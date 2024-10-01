#include "user.h"
#include <string.h>
#include <stdio.h>

#define MAX_USERS 10
#define USERNAME_LEN 20
#define PASSWORD_LEN 20

typedef struct {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    int is_root;
} User;

User users[MAX_USERS];
int user_count = 0;
int current_user_index = -1; // -1 for no user logged in

void init_users() {
    // Add users
    strcpy(users[user_count].username, "root");
    strcpy(users[user_count].password, "rootpass");
    users[user_count++].is_root = 1;

    strcpy(users[user_count].username, "user");
    strcpy(users[user_count].password, "userpass");
    users[user_count++].is_root = 0;
}

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0) {
            current_user_index = i;
            return 1; // Successful authentication
        }
    }
    return 0; // Failed authentication
}

void login_prompt() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];

    print_message("Username: ");
    gets(username); // Insecure, should be replaced
    print_message("Password: ");
    gets(password); // Insecure, should be replaced

    if (authenticate(username, password)) {
        print_message("Login successful.");
    } else {
        print_message("Login failed.");
    }
}
