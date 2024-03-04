#include <stdio.h>
#include <stdlib.h>

#define MATRIX_SIZE 3

int key[MATRIX_SIZE][MATRIX_SIZE];

void hillEncrypt(char *plaintext, char *ciphertext) {

    int x[MATRIX_SIZE],i,j;
    int y[MATRIX_SIZE];

    for ( i = 0; i < MATRIX_SIZE; i++) {
        x[i] = plaintext[i] - 'a';
    }

    for (i = 0; i < MATRIX_SIZE; i++) {
        y[i] = 0;
        for (j = 0; j < MATRIX_SIZE; j++) {
            y[i] += key[i][j] * x[j];
        }
        y[i] %= 26; 

    for ( i = 0; i < MATRIX_SIZE; i++) {
        ciphertext[i] = y[i] + 'a';
    }
    ciphertext[MATRIX_SIZE] = '\0';
}
}

int main() {
    char plaintext[MATRIX_SIZE + 1]; 
    char ciphertext[MATRIX_SIZE + 1]; 
    int i,j;

    printf("Enter the key matrix for Hill cipher (3x3):\n");
    for ( i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            scanf("%d", &key[i][j]);
        }
    }

    printf("Enter the plaintext (3 characters): ");
    scanf("%s",&plaintext);

    hillEncrypt(plaintext,ciphertext);

    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}

