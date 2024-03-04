#include <stdio.h>
#include <string.h>

int charExists(char *str, char ch) {
	int i;
    for ( i = 0; i < strlen(str); i++) {
        if (str[i] == ch) {
            return 1; 
        }
    }
    return 0; 
}

unsigned long long calculatePossibleKeys(char *key) {
  
    int matrixSize = 25,i;

    char usedLetters[matrixSize];
    memset(usedLetters, '\0', sizeof(usedLetters));

    int index = 0;

    for ( i = 0; i < strlen(key); i++) {
        if (key[i] != ' ' && !charExists(usedLetters, key[i])) {
            usedLetters[index++] = key[i];
        }
    }

    int emptySlots = matrixSize - index;

    unsigned long long possibleKeys = 1;
    for ( i = matrixSize; i > emptySlots; i--) {
        possibleKeys *= i;
    }

    return possibleKeys;
}

int main() {
    char key[26];

    printf("Enter the key for the Playfair cipher (without spaces): ");
    scanf("%s", key);

    unsigned long long keys = calculatePossibleKeys(key);
    printf("Number of possible keys: %llu\n", keys);

    return 0;
}
