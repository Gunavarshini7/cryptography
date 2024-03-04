#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

void calculateLetterFrequencies(char *text, double frequencies[]) {
    int totalLetters = 0;
    int i;

   
    for (i = 0; i < ALPHABET_SIZE; i++) {
        frequencies[i] = 0.0;
    }


    for (i = 0; text[i] != '\0'; i++) {
        char c = text[i];
        if (isalpha(c)) {
            frequencies[tolower(c) - 'a']++;
            totalLetters++;
        }
    }

    for (i = 0; i < ALPHABET_SIZE; i++) {
        frequencies[i] /= totalLetters;
    }
}

void decrypt(char *ciphertext, int key) {
    int length = strlen(ciphertext),i;
    char plaintext[length + 1];

   
    for (i = 0; i < length; i++) {
        char c = ciphertext[i];
        if (isalpha(c)) {
            if (isupper(c)) {
                plaintext[i] = ((c - 'A' - key + 26) % 26) + 'A';
            } else {
                plaintext[i] = ((c - 'a' - key + 26) % 26) + 'a';
            }
        } else {
            plaintext[i] = c;
        }
    }
    plaintext[length] = '\0';

    printf("Key: %d, Plaintext: %s\n", key, plaintext);
}

void rankPlaintexts(char *ciphertext, int topN) {
    double englishFrequencies[ALPHABET_SIZE] = {0.0817, 0.0149, 0.0278, 0.0425, 0.1270, 0.0223, 0.0202, 0.0609, 0.0697, 0.0015, 0.0077, 0.0403, 0.0241, 0.0675, 0.0751, 0.0193, 0.0009, 0.0599, 0.0633, 0.0906, 0.0276, 0.0098, 0.0236, 0.0015, 0.0197, 0.0007};
    int length = strlen(ciphertext),key,i;

    for ( key = 0; key < ALPHABET_SIZE; key++) {
        char decrypted[length + 1];
        double frequencies[ALPHABET_SIZE];
        memcpy(decrypted, ciphertext, length + 1);
        decrypt(decrypted, key);
        calculateLetterFrequencies(decrypted, frequencies);
        double score = 0.0;

        
        for ( i = 0; i < ALPHABET_SIZE; i++) {
            score += (englishFrequencies[i] - frequencies[i]) * (englishFrequencies[i] - frequencies[i]);
        }

        printf("Similarity Score: %lf\n", score);
    }
}

int main() {
    char ciphertext[] = "Vg wvv dliw khdho dsvv, wkh qdwlrq ri wkh dssurydo.";
    int topN = 10;

    printf("Performing letter frequency attack on the ciphertext:\n%s\n", ciphertext);
    printf("Finding top %d possible plaintexts:\n", topN);
    rankPlaintexts(ciphertext, topN);

    return 0;
}
