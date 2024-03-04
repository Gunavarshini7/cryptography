#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 8

void handleError(const char* message) {
    perror(message);
    exit(EXIT_FAILURE);
}

// Simple substitution-permutation network (SPN) encryption function
void encrypt_ecb(const char* input, const char* key, char* output) {
    size_t blockLength = strlen(input);

    for (size_t i = 0; i < blockLength; i++) {
        output[i] = input[i] ^ key[i % BLOCK_SIZE];  // Basic XOR operation as a substitute for encryption
    }
}

int main() {
    const char* plaintext = "Hello, ECB mode!";
    const char* key = "01234567";  // 8 bytes key for demonstration

    // Output buffer should be large enough to accommodate padding
    char ciphertext[256];

    // Calculate the number of blocks needed
    size_t len = strlen(plaintext);
    size_t numBlocks = (len + BLOCK_SIZE - 1) / BLOCK_SIZE;

    // Process each block independently
    for (size_t i = 0; i < numBlocks; i++) {
        const char* blockStart = plaintext + i * BLOCK_SIZE;
        char* outputBlock = ciphertext + i * BLOCK_SIZE;

        // Pad the last block if needed
        size_t blockLength = (i == numBlocks - 1) ? (len % BLOCK_SIZE == 0 ? BLOCK_SIZE : len % BLOCK_SIZE) : BLOCK_SIZE;

        // Encrypt the block
        encrypt_ecb(blockStart, key, outputBlock);
    }

    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: ");
    for (size_t i = 0; i < len; i++) {
        printf("%02x", (unsigned char)ciphertext[i]);
    }
    printf("\n");

    return 0;
}

