#include <stdio.h>
#include <string.h>

#define SIZE 5

void findPosition(char keyMatrix[SIZE][SIZE], char ch, int *row, int *col) {
    if (ch == 'J')
        ch = 'I';

    for (*row = 0; *row < SIZE; (*row)++)
        for (*col = 0; *col < SIZE; (*col)++)
            if (keyMatrix[*row][*col] == ch)
                return;
}

void decryptPlayfair(char cipher[2], char keyMatrix[SIZE][SIZE]) {
    int row1, col1, row2, col2;

    findPosition(keyMatrix, cipher[0], &row1, &col1);
    findPosition(keyMatrix, cipher[1], &row2, &col2);

    if (row1 == row2) {
        col1 = (col1 - 1 + SIZE) % SIZE;
        col2 = (col2 - 1 + SIZE) % SIZE;
    }
  
    else if (col1 == col2) {
        row1 = (row1 - 1 + SIZE) % SIZE;
        row2 = (row2 - 1 + SIZE) % SIZE;
    }
 
    else {
        int temp = col1;
        col1 = col2;
        col2 = temp;
    }

    printf("%c%c", keyMatrix[row1][col1], keyMatrix[row2][col2]);
}

void decryptMessage(char *message, char keyMatrix[SIZE][SIZE]) {
	int i;
    for ( i = 0; i < strlen(message); i += 2) {
        char cipher[2];
        cipher[0] = message[i];
        cipher[1] = message[i + 1];

        decryptPlayfair(cipher, keyMatrix);
    }
}

int main() {
    
    char keyMatrix[SIZE][SIZE] = {
        {'K', 'X', 'J', 'E', 'Y'},
        {'U', 'R', 'E', 'B', 'E'},
        {'Z', 'W', 'E', 'H', 'E'},
        {'W', 'R', 'Y', 'T', 'U'},
        {'H', 'E', 'Y', 'F', 'S'}
    };

   
    char message[] = "KXJEYUREBEZWEHEWRYTUHEYFSKREHEGOYFIWTTTUOLKSYCAJPOBOTEIZONTXBYBNTGONEYCUZWRGDSONSXBOUYWRHEBAAHYUSEDQ";

    printf("Playfair Decoded Message: ");
    decryptMessage(message, keyMatrix);

    return 0;
}
