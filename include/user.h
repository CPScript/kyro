#ifndef USER_H
#define USER_H

#include <stdbool.h>

#define MAX_USERS 10
#define USERNAME_LENGTH 12
#define PASSWORD_LENGTH 12

typedef struct {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
    bool is_admin; // Flag for user roles
} User;

User user_list[MAX_USERS]; // Array to store users
int user_count = 0;         // Count of registered users

bool add_user(const char *username, const char *password, bool is_admin);
bool authenticate(const char *username, const char *password);

#endif // USER_H
