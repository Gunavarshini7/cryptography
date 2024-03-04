#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 8

// Mock S-DES encryption function (for educational purposes)
void sdes_encrypt(int plaintext[BLOCK_SIZE], int key[10], int ciphertext[BLOCK_SIZE]) {
	int i;
    // This should be replaced with the actual S-DES encryption steps.
    // For the sake of demonstration, we'll simulate it with a simple operation.
    for (i = 0; i < BLOCK_SIZE; ++i) {
        ciphertext[i] = plaintext[i] ^ ((key[i % 10] + i) % 2);
    }
}

// Mock S-DES decryption function (symmetric with the mock encryption for demonstration)
void sdes_decrypt(int ciphertext[BLOCK_SIZE], int key[10], int plaintext[BLOCK_SIZE]) {
    // Since our mock encryption is symmetric, decryption is the same
    sdes_encrypt(ciphertext, key, plaintext);
}

// XOR operation for two blocks of binary data
void xor_blocks(int block1[BLOCK_SIZE], int block2[BLOCK_SIZE], int result[BLOCK_SIZE]) {
	int i;
    for (i = 0; i < BLOCK_SIZE; ++i) {
        result[i] = block1[i] ^ block2[i];
    }
}

// CBC mode encryption using S-DES
void cbc_encrypt(int plaintext[][BLOCK_SIZE], int key[10], int iv[BLOCK_SIZE], int ciphertext[][BLOCK_SIZE], int num_blocks) {
    int temp[BLOCK_SIZE],i;

    for (i = 0; i < num_blocks; ++i) {
        if (i == 0) {
            xor_blocks(plaintext[i], iv, temp);
        } else {
            xor_blocks(plaintext[i], ciphertext[i - 1], temp);
        }
        sdes_encrypt(temp, key, ciphertext[i]);
    }
}

// CBC mode decryption using S-DES
void cbc_decrypt(int ciphertext[][BLOCK_SIZE], int key[10], int iv[BLOCK_SIZE], int plaintext[][BLOCK_SIZE], int num_blocks) {
    int temp[BLOCK_SIZE],i;

    for (i = num_blocks - 1; i >= 0; --i) {
        sdes_decrypt(ciphertext[i], key, temp);
        if (i == 0) {
            xor_blocks(temp, iv, plaintext[i]);
        } else {
            xor_blocks(temp, ciphertext[i - 1], plaintext[i]);
        }
    }
}

int main() {
    // Test data
    int plaintext[2][BLOCK_SIZE] = {{0, 0, 0, 0, 0, 0, 0, 1}, {0, 0, 1, 0, 0, 0, 1, 1}};
    int key[10] = {0, 1, 1, 1, 1, 1, 1, 1, 0, 1};
    int iv[BLOCK_SIZE] = {1, 0, 1, 0, 1, 0, 1, 0};
    int ciphertext[2][BLOCK_SIZE];
    int decrypted[2][BLOCK_SIZE];
    int num_blocks = 2;

    // Encrypt
    cbc_encrypt(plaintext, key, iv, ciphertext, num_blocks);
    int i,j;
    printf("Ciphertext:\n");
    for ( i = 0; i < num_blocks; ++i) {
        for ( j = 0; j < BLOCK_SIZE; ++j) {
            printf("%d", ciphertext[i][j]);
        }
        printf("\n");
    }

    // Decrypt
    cbc_decrypt(ciphertext, key, iv, decrypted, num_blocks);
    printf("Decrypted Text:\n");
    for (i = 0; i < num_blocks; ++i) {
        for (j = 0; j < BLOCK_SIZE; ++j) {
            printf("%d", decrypted[i][j]);
        }
        printf("\n");
    }

    return 0;
}

