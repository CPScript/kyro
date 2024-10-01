#include "user.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_USERNAME_LENGTH 12
#define MAX_PASSWORD_LENGTH 12

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    uint8_t password_hash[MAX_PASSWORD_LENGTH];
    bool is_admin;
} User;

User user_list[MAX_USERS];
int user_count = 0;

bool add_user(const char *username, const char *password, bool is_admin) {
    if (user_count >= MAX_USERS) {
        printf("User limit reached.\n");
        return false;
    }
    if (strlen(username) == 0) {
        printf("Username cannot be empty.\n");
        return false;
    }
    if (strlen(username) >= MAX_USERNAME_LENGTH) {
        printf("Username too long.\n");
        return false;
    }
    if (strlen(password) == 0) {
        printf("Password cannot be empty.\n");
        return false;
    }
    if (strlen(password) >= MAX_PASSWORD_LENGTH) {
        printf("Password too long.\n");
        return false;
    }
    strcpy(user_list[user_count].username, username);
    // Simple password hashing for demonstration purposes only
    for (int i = 0; i < MAX_PASSWORD_LENGTH; i++) {
        user_list[user_count].password_hash[i] = password[i];
    }
    user_list[user_count].is_admin = is_admin;
    user_count++;
    return true;
}

bool authenticate(const char *username, const char *password) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(user_list[i].username, username) == 0) {
            // Simple password verification for demonstration purposes only
            for (int j = 0; j < MAX_PASSWORD_LENGTH; j++) {
                if (user_list[i].password_hash[j] != password[j]) {
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}
