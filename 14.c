#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void encrypt(char *plaintext, int *key, char *ciphertext) {
    int i;
    int key_length = strlen(plaintext); // Use plaintext length as key length
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            int shift = key[i % key_length];
            if (isupper(plaintext[i])) {
                ciphertext[i] = 'A' + (plaintext[i] - 'A' + shift) % 26;
            } else {
                ciphertext[i] = 'a' + (plaintext[i] - 'a' + shift) % 26;
            }
        } else {
            ciphertext[i] = plaintext[i]; // Preserve non-alphabetic characters
        }
    }
    ciphertext[i] = '\0';
}

int main() {
    char plaintext[1000];
    int key[1000];
    char ciphertext[1000];

    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    if (strlen(plaintext) > 0 && plaintext[strlen(plaintext) - 1] == '\n') {
        plaintext[strlen(plaintext) - 1] = '\0';
    }

    printf("Enter key (space-separated integers between 0 and 26): ");
    int i = 0;
    char key_input[1000];
    fgets(key_input, sizeof(key_input), stdin);

    char *token = strtok(key_input, " ");
    while (token != NULL && i < 1000) {
        key[i++] = atoi(token);
        token = strtok(NULL, " ");
    }

    encrypt(plaintext, key, ciphertext);

  
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
