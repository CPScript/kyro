#include "user.h"
#include <string.h>
#include <stdio.h>

unsigned long hash_password(const char *password) {
    unsigned long hash = 5381;
    int c;
    while ((c = *password++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash;
}

bool add_user(const char *username, const char *password, bool is_admin) {
    if (user_count >= MAX_USERS) {
        printf("User limit reached.\n");
        return false;
    }
    if (strlen(username) >= USERNAME_LENGTH) {
        printf("Username too long.\n");
        return false;
    }
    strcpy(user_list[user_count].username, username);
    user_list[user_count].password_hash = hash_password(password);
    user_list[user_count].is_admin = is_admin;
    user_count++;
    return true;
}

bool authenticate(const char *username, const char *password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(user_list[i].username, username) == 0 &&
            user_list[i].password_hash == hash_password(password)) {
            return true; // Successful authentication
        }
    }
    return false; // Authentication failed
}
