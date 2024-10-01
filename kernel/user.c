#include "user.h"
#include <string.h>
#include <stdio.h>

bool add_user(const char *username, const char *password, bool is_admin) {
    if (user_count >= MAX_USERS) {
        printf("User limit reached.\n");
        return false;
    }
    strcpy(user_list[user_count].username, username);
    strcpy(user_list[user_count].password, password);
    user_list[user_count].is_admin = is_admin;
    user_count++;
    return true;
}

bool authenticate(const char *username, const char *password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(user_list[i].username, username) == 0 &&
            strcmp(user_list[i].password, password) == 0) {
            return true; // Successful authentication
        }
    }
    return false; // Authentication failed
}
