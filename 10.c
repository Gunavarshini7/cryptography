#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ROWS 5
#define COLS 5
void findPosition(char key[][COLS], char letter, int *row, int *col) {
    int i, j;
    for (i = 0; i < ROWS; ++i) {
        for (j = 0; j < COLS; ++j) {
            if (key[i][j] == letter || (key[i][j] == 'J' && letter == 'I')) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}
void encryptPair(char key[][COLS], char a, char b, char *cipher) {
    int row1, col1, row2, col2;
    findPosition(key, a, &row1, &col1);
    findPosition(key, b, &row2, &col2);
    
    if (row1 == row2) { 
        cipher[0] = key[row1][(col1 + 1) % COLS];
        cipher[1] = key[row2][(col2 + 1) % COLS];
    } else if (col1 == col2) { 
        cipher[0] = key[(row1 + 1) % ROWS][col1];
        cipher[1] = key[(row2 + 1) % ROWS][col2];
    } else { 
        cipher[0] = key[row1][col2];
        cipher[1] = key[row2][col1];
    }
}
void playfairEncrypt(char key[][COLS], const char *message, char *cipher) {
    int i = 0;
    while (i < strlen(message)) {
        char a = toupper(message[i]);
        char b = (i + 1 < strlen(message)) ? toupper(message[i + 1]) : 'X';
        if (!isalpha(a)) {
            cipher[i] = a;
            ++i;
            continue;
        }
        if (!isalpha(b)) {
            b = 'X';
            --i; 
        }
        encryptPair(key, a, b, &cipher[i]);
        i += 2;
    }
    cipher[i] = '\0';
}

int main() {
    char key[ROWS][COLS] = {
        {'M', 'F', 'H', 'I', 'K'},
        {'U', 'N', 'O', 'P', 'Q'},
        {'Z', 'V', 'W', 'X', 'Y'},
        {'E', 'L', 'A', 'R', 'G'},
        {'D', 'S', 'T', 'B', 'C'}
    };

    const char *message = "see you at the hotel";
    char cipher[100];

    playfairEncrypt(key, message, cipher);

    printf("Original Message: %s\n", message);
    printf("Encrypted Message: %s\n", cipher);

    return 0;
}
