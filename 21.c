#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 8 // Example block size

// Prototype for the "encryption" function
void xor_encrypt(const char *input, const char *key, char *output, size_t len);

// Adds padding to the input as per PKCS#5/PKCS#7
size_t add_padding(char *input, size_t input_len) {
    size_t padding_len = BLOCK_SIZE - (input_len % BLOCK_SIZE);
    size_t i;
    char padding_value = padding_len;
    for (i = input_len; i < input_len + padding_len; i++) {
        input[i] = padding_value;
    }
    return input_len + padding_len; // New length after padding
}

// ECB mode encryption
void ecb_encrypt(const char *plaintext, size_t pt_len, const char *key, char *ciphertext) {
	size_t i;
    for (i = 0; i < pt_len; i += BLOCK_SIZE) {
        xor_encrypt(plaintext + i, key, ciphertext + i, BLOCK_SIZE);
    }
}

// CBC mode encryption
void cbc_encrypt(const char *plaintext, size_t pt_len, const char *key, const char *iv, char *ciphertext) {
    char prev_block[BLOCK_SIZE];
    size_t i,j;
    memcpy(prev_block, iv, BLOCK_SIZE);

    for (i = 0; i < pt_len; i += BLOCK_SIZE) {
        for (j = 0; j < BLOCK_SIZE; j++) {
            prev_block[j] ^= plaintext[i + j];
        }
        xor_encrypt(prev_block, key, ciphertext + i, BLOCK_SIZE);
        memcpy(prev_block, ciphertext + i, BLOCK_SIZE);
    }
}

// Example "encryption" function (XOR for demonstration)
void xor_encrypt(const char *input, const char *key, char *output, size_t len) {
	size_t i;
    for (i = 0; i < len; i++) {
        output[i] = input[i] ^ key[i % BLOCK_SIZE];
    }
}

int main() {
    char plaintext[64] = "This is a secret message!";
    size_t pt_len = strlen(plaintext),i;
    const char *key = "secretky"; // Example key
    char iv[BLOCK_SIZE] = {0}; // Initialization vector for CBC

    // Add padding to plaintext
    pt_len = add_padding(plaintext, pt_len);

    char ecb_ciphertext[64] = {0};
    char cbc_ciphertext[64] = {0};

    // ECB encryption
    ecb_encrypt(plaintext, pt_len, key, ecb_ciphertext);

    // CBC encryption
    cbc_encrypt(plaintext, pt_len, key, iv, cbc_ciphertext);

    printf("Plaintext: %s\n", plaintext);
    printf("ECB Ciphertext: ");
    for(i = 0; i < pt_len; i++) {
        printf("%02hhx", ecb_ciphertext[i]);
    }
    printf("\n");

    printf("CBC Ciphertext: ");
    for( i = 0; i < pt_len; i++) {
        printf("%02hhx", cbc_ciphertext[i]);
    }
    printf("\n");

    return 0;
}

