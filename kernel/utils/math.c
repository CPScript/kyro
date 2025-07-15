#include <stdint.h>
#include <stdbool.h>

// Basic arithmetic operations
int abs(int x) {
    return (x < 0) ? -x : x;
}

long labs(long x) {
    return (x < 0) ? -x : x;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

// Power function
int pow(int base, int exp) {
    if (exp == 0) return 1;
    if (exp < 0) return 0; // Integer division would truncate
    
    int result = 1;
    while (exp > 0) {
        if (exp & 1) {
            result *= base;
        }
        base *= base;
        exp >>= 1;
    }
    return result;
}

// Square root using Newton's method
int sqrt(int x) {
    if (x < 0) return -1;
    if (x == 0) return 0;
    
    int guess = x / 2;
    int prev_guess = 0;
    
    while (guess != prev_guess) {
        prev_guess = guess;
        guess = (guess + x / guess) / 2;
    }
    
    return guess;
}

// GCD using Euclidean algorithm
int gcd(int a, int b) {
    a = abs(a);
    b = abs(b);
    
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// LCM calculation
int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

// Modular arithmetic
int mod(int a, int b) {
    if (b == 0) return 0;
    int result = a % b;
    return (result < 0) ? result + b : result;
}

// Fast modular exponentiation
long mod_pow(long base, long exp, long mod) {
    if (mod == 1) return 0;
    
    long result = 1;
    base = base % mod;
    
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % mod;
        }
        exp >>= 1;
        base = (base * base) % mod;
    }
    
    return result;
}

// Bit manipulation utilities
int popcount(uint32_t x) {
    int count = 0;
    while (x) {
        count++;
        x &= x - 1; // Clear least significant bit
    }
    return count;
}

int clz(uint32_t x) {
    if (x == 0) return 32;
    
    int count = 0;
    if (!(x & 0xFFFF0000)) { count += 16; x <<= 16; }
    if (!(x & 0xFF000000)) { count += 8;  x <<= 8;  }
    if (!(x & 0xF0000000)) { count += 4;  x <<= 4;  }
    if (!(x & 0xC0000000)) { count += 2;  x <<= 2;  }
    if (!(x & 0x80000000)) { count += 1;  }
    
    return count;
}

int ctz(uint32_t x) {
    if (x == 0) return 32;
    
    int count = 0;
    if (!(x & 0x0000FFFF)) { count += 16; x >>= 16; }
    if (!(x & 0x000000FF)) { count += 8;  x >>= 8;  }
    if (!(x & 0x0000000F)) { count += 4;  x >>= 4;  }
    if (!(x & 0x00000003)) { count += 2;  x >>= 2;  }
    if (!(x & 0x00000001)) { count += 1;  }
    
    return count;
}

// Round to nearest power of 2
uint32_t round_up_pow2(uint32_t x) {
    if (x <= 1) return 1;
    
    x--;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    x++;
    
    return x;
}

// Check if number is power of 2
bool is_pow2(uint32_t x) {
    return x && !(x & (x - 1));
}

// Align value to boundary
uint32_t align_up(uint32_t value, uint32_t alignment) {
    return (value + alignment - 1) & ~(alignment - 1);
}

uint32_t align_down(uint32_t value, uint32_t alignment) {
    return value & ~(alignment - 1);
}

// Byte swap operations
uint16_t bswap16(uint16_t x) {
    return ((x & 0xFF) << 8) | ((x & 0xFF00) >> 8);
}

uint32_t bswap32(uint32_t x) {
    return ((x & 0xFF) << 24) |
           ((x & 0xFF00) << 8) |
           ((x & 0xFF0000) >> 8) |
           ((x & 0xFF000000) >> 24);
}

// Random number generator (Linear Congruential Generator)
static uint32_t rand_seed = 1;

void srand(uint32_t seed) {
    rand_seed = seed;
}

uint32_t rand() {
    rand_seed = (rand_seed * 1103515245 + 12345) & 0x7FFFFFFF;
    return rand_seed;
}

// Division with remainder
typedef struct {
    int quotient;
    int remainder;
} div_t;

div_t div(int numerator, int denominator) {
    div_t result;
    result.quotient = numerator / denominator;
    result.remainder = numerator % denominator;
    return result;
}

// Checksum calculations
uint32_t checksum32(const void *data, size_t len) {
    const uint32_t *ptr = (const uint32_t *)data;
    uint32_t sum = 0;
    
    while (len >= 4) {
        sum += *ptr++;
        len -= 4;
    }
    
    // Handle remaining bytes
    const uint8_t *byte_ptr = (const uint8_t *)ptr;
    while (len > 0) {
        sum += *byte_ptr++;
        len--;
    }
    
    return sum;
}

uint16_t checksum16(const void *data, size_t len) {
    const uint16_t *ptr = (const uint16_t *)data;
    uint32_t sum = 0;
    
    while (len >= 2) {
        sum += *ptr++;
        len -= 2;
    }
    
    // Handle odd byte
    if (len == 1) {
        sum += *(const uint8_t *)ptr;
    }
    
    // Fold 32-bit sum to 16 bits
    while (sum >> 16) {
        sum = (sum & 0xFFFF) + (sum >> 16);
    }
    
    return (uint16_t)sum;
}
