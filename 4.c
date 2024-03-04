#include <stdio.h>
#include <ctype.h>
#include <string.h>

void vigenereEncrypt(char *plaintext, char *key) {
    int i, j;
    int plaintextLen = strlen(plaintext);
    int keyLen = strlen(key);

    for (i = 0, j = 0; i < plaintextLen; ++i, ++j) {
       
        if (j == keyLen)
            j = 0;

        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            plaintext[i] = (char)((toupper(plaintext[i]) + key[j] - 2 * base) % 26 + base);
        }
    }
}

int main() {
    char plaintext[1000];
    char key[100];

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);

    size_t plaintextLen = strlen(plaintext);
    if (plaintext[plaintextLen - 1] == '\n')
        plaintext[plaintextLen - 1] = '\0';

    size_t keyLen = strlen(key);
    if (key[keyLen - 1] == '\n')
        key[keyLen - 1] = '\0';

    vigenereEncrypt(plaintext, key);

    printf("Encrypted text: %s\n", plaintext);

    return 0;
}
