#include "user.h"
#include <string.h>

#define MAX_USERS 10
#define USERNAME_LEN 20

typedef struct {
    char username[USERNAME_LEN];
    int is_root;
} User;

User users[MAX_USERS];
int user_count = 0;

void init_users() {
    // root user
    strcpy(users[user_count].username, "root");
    users[user_count++].is_root = 1;

    // regular user
    strcpy(users[user_count].username, "user");
    users[user_count++].is_root = 0;
}
