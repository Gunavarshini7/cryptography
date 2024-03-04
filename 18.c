#include <stdio.h>
#include <stdint.h>

// Function to perform bitwise circular left shift by n positions
uint32_t circularLeftShift(uint32_t input, int n) {
    return ((input << n) | (input >> (32 - n))) & 0xFFFFFFFF;
}

// Generate 16 subkeys for DES
void generateSubKeys(uint64_t key, uint64_t subKeys[16]) {
    // Initial permutation choice (PC1) to select 56 bits from the 64-bit key
    uint64_t permutedChoice = 0;
    int i,round;
    const int pc1[] = {
        57, 49, 41, 33, 25, 17, 9,
        1,  58, 50, 42, 34, 26, 18,
        10, 2,  59, 51, 43, 35, 27,
        19, 11, 3,  60, 52, 44, 36,
        63, 55, 47, 39, 31, 23, 15,
        7,  62, 54, 46, 38, 30, 22,
        14, 6,  61, 53, 45, 37, 29,
        21, 13, 5,  28, 20, 12, 4
    };

    // Apply permutation choice to the key
    for (i = 0; i < 56; i++) {
        permutedChoice <<= 1;
        permutedChoice |= (key >> (64 - pc1[i])) & 0x01;
    }

    // Split permuted choice into left and right halves
    uint32_t left = permutedChoice >> 28;
    uint32_t right = permutedChoice & 0x0FFFFFFF;

    // Key schedule generation
    for (round = 0; round < 16; round++) {
        // Perform circular left shift on both halves
        left = circularLeftShift(left, 1);
        right = circularLeftShift(right, 1);

        // Combine left and right halves
        uint64_t combined = ((uint64_t)left << 28) | right;

        // Permutation choice 2 (PC2) to select 48 bits from the combined 56 bits
        const int pc2[] = {
            14, 17, 11, 24, 1,  5,
            3,  28, 15, 6,  21, 10,
            23, 19, 12, 4,  26, 8,
            16, 7,  27, 20, 13, 2,
            41, 52, 31, 37, 47, 55,
            30, 40, 51, 45, 33, 48,
            44, 49, 39, 56, 34, 53,
            46, 42, 50, 36, 29, 32
        };

        uint64_t subKey = 0;
        for ( i = 0; i < 48; i++) {
            subKey <<= 1;
            subKey |= (combined >> (56 - pc2[i])) & 0x01;
        }

        // Store the generated subkey
        subKeys[round] = subKey;
    }
}

int main() {
    uint64_t initialKey = 0x0123456789ABCDEF;  // Example 64-bit key
    uint64_t subKeys[16];
    int i;

    generateSubKeys(initialKey, subKeys);

    // Print the generated subkeys
    printf("Generated Subkeys:\n");
    for ( i = 0; i < 16; i++) {
        printf("%d: %llx\n", i + 1, subKeys[i]);
    }

    return 0;
}

