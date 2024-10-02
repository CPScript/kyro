// simple encryption
// aes.c

#include <openssl/aes.h>

void encrypt_data(void *data, int size) {
    // Set up the AES encryption algorithm
    AES_KEY aes_key;
    AES_set_encrypt_key("secret_key", 128, &aes_key);

    // Encrypt the data
    AES_encrypt(data, data, &aes_key, size);
}
