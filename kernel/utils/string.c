#include <stdint.h>
#include <stdbool.h>

// String length
size_t strlen(const char *s) {
    size_t len = 0;
    while (*s++) {
        len++;
    }
    return len;
}

// String copy
char *strcpy(char *dest, const char *src) {
    char *original_dest = dest;
    while ((*dest++ = *src++));
    return original_dest;
}

// String copy with length limit
char *strncpy(char *dest, const char *src, size_t n) {
    char *original_dest = dest;
    
    while (n > 0 && *src) {
        *dest++ = *src++;
        n--;
    }
    
    // Pad with null bytes if necessary
    while (n > 0) {
        *dest++ = '\0';
        n--;
    }
    
    return original_dest;
}

// String concatenation
char *strcat(char *dest, const char *src) {
    char *original_dest = dest;
    
    // Find end of destination string
    while (*dest) {
        dest++;
    }
    
    // Append source string
    while ((*dest++ = *src++));
    
    return original_dest;
}

// String concatenation with length limit
char *strncat(char *dest, const char *src, size_t n) {
    char *original_dest = dest;
    
    // Find end of destination string
    while (*dest) {
        dest++;
    }
    
    // Append up to n characters from source
    while (n > 0 && *src) {
        *dest++ = *src++;
        n--;
    }
    
    *dest = '\0'; // Null terminate
    
    return original_dest;
}

// String comparison
int strcmp(const char *s1, const char *s2) {
    while (*s1 && *s2 && *s1 == *s2) {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

// String comparison with length limit
int strncmp(const char *s1, const char *s2, size_t n) {
    while (n > 0 && *s1 && *s2 && *s1 == *s2) {
        s1++;
        s2++;
        n--;
    }
    
    if (n == 0) {
        return 0;
    }
    
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

// Case-insensitive string comparison
int strcasecmp(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        char c1 = (*s1 >= 'A' && *s1 <= 'Z') ? *s1 + 32 : *s1;
        char c2 = (*s2 >= 'A' && *s2 <= 'Z') ? *s2 + 32 : *s2;
        
        if (c1 != c2) {
            return c1 - c2;
        }
        
        s1++;
        s2++;
    }
    
    char c1 = (*s1 >= 'A' && *s1 <= 'Z') ? *s1 + 32 : *s1;
    char c2 = (*s2 >= 'A' && *s2 <= 'Z') ? *s2 + 32 : *s2;
    
    return c1 - c2;
}

// Find character in string
char *strchr(const char *s, int c) {
    while (*s) {
        if (*s == c) {
            return (char *)s;
        }
        s++;
    }
    
    return (c == '\0') ? (char *)s : NULL;
}

// Find last occurrence of character in string
char *strrchr(const char *s, int c) {
    const char *last = NULL;
    
    while (*s) {
        if (*s == c) {
            last = s;
        }
        s++;
    }
    
    return (c == '\0') ? (char *)s : (char *)last;
}

// Find substring
char *strstr(const char *haystack, const char *needle) {
    if (!*needle) {
        return (char *)haystack;
    }
    
    while (*haystack) {
        const char *h = haystack;
        const char *n = needle;
        
        while (*h && *n && *h == *n) {
            h++;
            n++;
        }
        
        if (!*n) {
            return (char *)haystack;
        }
        
        haystack++;
    }
    
    return NULL;
}

// Case-insensitive substring search
char *strcasestr(const char *haystack, const char *needle) {
    if (!*needle) {
        return (char *)haystack;
    }
    
    while (*haystack) {
        const char *h = haystack;
        const char *n = needle;
        
        while (*h && *n) {
            char c1 = (*h >= 'A' && *h <= 'Z') ? *h + 32 : *h;
            char c2 = (*n >= 'A' && *n <= 'Z') ? *n + 32 : *n;
            
            if (c1 != c2) {
                break;
            }
            
            h++;
            n++;
        }
        
        if (!*n) {
            return (char *)haystack;
        }
        
        haystack++;
    }
    
    return NULL;
}

// String tokenization
char *strtok(char *str, const char *delim) {
    static char *next_token = NULL;
    
    if (str) {
        next_token = str;
    }
    
    if (!next_token) {
        return NULL;
    }
    
    // Skip leading delimiters
    while (*next_token && strchr(delim, *next_token)) {
        next_token++;
    }
    
    if (!*next_token) {
        return NULL;
    }
    
    char *token_start = next_token;
    
    // Find next delimiter
    while (*next_token && !strchr(delim, *next_token)) {
        next_token++;
    }
    
    if (*next_token) {
        *next_token++ = '\0';
    } else {
        next_token = NULL;
    }
    
    return token_start;
}

// Thread-safe string tokenization
char *strtok_r(char *str, const char *delim, char **saveptr) {
    if (str) {
        *saveptr = str;
    }
    
    if (!*saveptr) {
        return NULL;
    }
    
    // Skip leading delimiters
    while (**saveptr && strchr(delim, **saveptr)) {
        (*saveptr)++;
    }
    
    if (!**saveptr) {
        return NULL;
    }
    
    char *token_start = *saveptr;
    
    // Find next delimiter
    while (**saveptr && !strchr(delim, **saveptr)) {
        (*saveptr)++;
    }
    
    if (**saveptr) {
        *(*saveptr)++ = '\0';
    } else {
        *saveptr = NULL;
    }
    
    return token_start;
}

// String duplication
char *strdup(const char *s) {
    size_t len = strlen(s) + 1;
    char *dup = malloc(len);
    
    if (dup) {
        memcpy(dup, s, len);
    }
    
    return dup;
}

// String duplication with length limit
char *strndup(const char *s, size_t n) {
    size_t len = strlen(s);
    if (len > n) {
        len = n;
    }
    
    char *dup = malloc(len + 1);
    if (dup) {
        memcpy(dup, s, len);
        dup[len] = '\0';
    }
    
    return dup;
}

// String span functions
size_t strspn(const char *s, const char *accept) {
    size_t count = 0;
    
    while (*s && strchr(accept, *s)) {
        s++;
        count++;
    }
    
    return count;
}

size_t strcspn(const char *s, const char *reject) {
    size_t count = 0;
    
    while (*s && !strchr(reject, *s)) {
        s++;
        count++;
    }
    
    return count;
}

// Find any character from set
char *strpbrk(const char *s, const char *accept) {
    while (*s) {
        if (strchr(accept, *s)) {
            return (char *)s;
        }
        s++;
    }
    
    return NULL;
}

// Character classification
bool isalpha(int c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

bool isdigit(int c) {
    return c >= '0' && c <= '9';
}

bool isalnum(int c) {
    return isalpha(c) || isdigit(c);
}

bool isspace(int c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v';
}

bool isupper(int c) {
    return c >= 'A' && c <= 'Z';
}

bool islower(int c) {
    return c >= 'a' && c <= 'z';
}

bool isprint(int c) {
    return c >= 32 && c <= 126;
}

bool ispunct(int c) {
    return isprint(c) && !isalnum(c) && !isspace(c);
}

bool isxdigit(int c) {
    return isdigit(c) || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f');
}

// Character conversion
int toupper(int c) {
    return (c >= 'a' && c <= 'z') ? c - 32 : c;
}

int tolower(int c) {
    return (c >= 'A' && c <= 'Z') ? c + 32 : c;
}

// String conversion functions
int atoi(const char *str) {
    int result = 0;
    int sign = 1;
    
    // Skip whitespace
    while (isspace(*str)) {
        str++;
    }
    
    // Handle sign
    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }
    
    // Convert digits
    while (isdigit(*str)) {
        result = result * 10 + (*str - '0');
        str++;
    }
    
    return result * sign;
}
