#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CIPHERTEXT_SIZE 1024
#define ALPHABET_SIZE 26

// Function prototypes
void analyzeFrequency(const char *ciphertext, int *freq);
void sortFrequency(int *freq, char *sortedLetters);
int compare(const void *a, const void *b);
void decrypt(const char *ciphertext, char *plaintext, const char *key);
void generateKeyFromFreq(const int *cipherFreq, const char *sortedCipherLetters, char *key);

int main() {
    char ciphertext[MAX_CIPHERTEXT_SIZE];
    int freq[ALPHABET_SIZE] = {0};
    char sortedCipherLetters[ALPHABET_SIZE + 1] = "abcdefghijklmnopqrstuvwxyz";
    char key[ALPHABET_SIZE + 1];
    char plaintext[MAX_CIPHERTEXT_SIZE];
    int topN;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, MAX_CIPHERTEXT_SIZE, stdin);
    ciphertext[strcspn(ciphertext, "\n")] = 0; // Remove newline character if any

    analyzeFrequency(ciphertext, freq);
    sortFrequency(freq, sortedCipherLetters);

    // Generate a key based on frequency analysis - simplest approach
    generateKeyFromFreq(freq, sortedCipherLetters, key);

    printf("Generated key: %s\n", key);

    decrypt(ciphertext, plaintext, key);
    printf("Possible plaintext: %s\n", plaintext);

    // For simplicity, this example does not implement ranking of multiple plaintexts or interactive selection of top N possibilities.
    // Implementing a sophisticated ranking would require a more complex analysis of the text and possibly a dictionary to validate guesses.

    return 0;
}

void analyzeFrequency(const char *ciphertext, int *freq) {
    while (*ciphertext) {
        if (isalpha(*ciphertext)) {
            freq[tolower(*ciphertext) - 'a']++;
        }
        ciphertext++;
    }
}

void sortFrequency(int *freq, char *sortedLetters) {
    int indices[ALPHABET_SIZE],i,j;
    for ( i = 0; i < ALPHABET_SIZE; i++) {
        indices[i] = i; // Initialize indices to match positions in the alphabet
    }

    // Sort indices based on frequency
    for ( i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (j = 0; j < ALPHABET_SIZE - i - 1; j++) {
            if (freq[j] < freq[j + 1]) {
                // Swap frequencies
                int tempFreq = freq[j];
                freq[j] = freq[j + 1];
                freq[j + 1] = tempFreq;

                // Swap indices to maintain track of which letter is which
                int tempIndex = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = tempIndex;
            }
        }
    }

    // Map sorted indices back to letters
    for ( i = 0; i < ALPHABET_SIZE; i++) {
        sortedLetters[i] = 'a' + indices[i];
    }
    sortedLetters[ALPHABET_SIZE] = '\0'; // Null-terminate the string
}

void generateKeyFromFreq(const int *cipherFreq, const char *sortedCipherLetters, char *key) {
    // Mapping to English frequency, starting from most common letters to least
    const char *englishFreq = "etaoinshrdlcumwfgypbvkjxqz";
    int i;
    for ( i = 0; i < ALPHABET_SIZE; i++) {
        key[sortedCipherLetters[i] - 'a'] = englishFreq[i];
    }
    key[ALPHABET_SIZE] = '\0'; // Null-terminate the string
}

void decrypt(const char *ciphertext, char *plaintext, const char *key) {
    while (*ciphertext) {
        if (isalpha(*ciphertext)) {
            if (islower(*ciphertext)) {
                *plaintext++ = key[*ciphertext - 'a'];
            } else {
                *plaintext++ = toupper(key[tolower(*ciphertext) - 'a']);
            }
        } else {
            *plaintext++ = *ciphertext;
        }
        ciphertext++;
    }
    *plaintext = '\0'; // Null-terminate the string
}

