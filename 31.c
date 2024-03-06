#include <stdio.h>
#include <stdint.h>

#define BLOCK_SIZE 8 // Block size in bytes (64 bits)

void block_cipher_encrypt(uint8_t *output, const uint8_t *input, const uint8_t *key) {
	int i;
    // Placeholder for a block cipher encryption function (e.g., AES) using key
    // For simplicity, we'll XOR the input with the key (not secure in practice)
    for (i = 0; i < BLOCK_SIZE; i++) {
        output[i] = input[i] ^ key[i];
    }
}

void generate_subkeys(uint8_t *subkey1, uint8_t *subkey2, const uint8_t *key) {
    uint8_t zero_block[BLOCK_SIZE] = {0};
    int i;

    // Generate the first subkey
    block_cipher_encrypt(subkey1, zero_block, key);

    // Perform left shift by one bit
    int carry = (subkey1[0] & 0x80) ? 1 : 0;
    for ( i = 0; i < BLOCK_SIZE - 1; i++) {
        subkey1[i] = (subkey1[i] << 1) | (subkey1[i + 1] >> 7);
    }
    subkey1[BLOCK_SIZE - 1] = (subkey1[BLOCK_SIZE - 1] << 1) ^ (carry ? 0x1B : 0x00); // XOR constant

    // Generate the second subkey
    block_cipher_encrypt(subkey2, subkey1, key);

    // Perform left shift by one bit
    carry = (subkey2[0] & 0x80) ? 1 : 0;
    for ( i = 0; i < BLOCK_SIZE - 1; i++) {
        subkey2[i] = (subkey2[i] << 1) | (subkey2[i + 1] >> 7);
    }
    subkey2[BLOCK_SIZE - 1] = (subkey2[BLOCK_SIZE - 1] << 1) ^ (carry ? 0x1B : 0x00); // XOR constant
}

int main() {
    uint8_t key[BLOCK_SIZE] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6}; // Example key
    uint8_t subkey1[BLOCK_SIZE];
    uint8_t subkey2[BLOCK_SIZE];
    int i;

    generate_subkeys(subkey1, subkey2, key);

    printf("Subkey 1: ");
    for (i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x ", subkey1[i]);
    }
    printf("\n");

    printf("Subkey 2: ");
    for ( i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x ", subkey2[i]);
    }
    printf("\n");

    return 0;
}

