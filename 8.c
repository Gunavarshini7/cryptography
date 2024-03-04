#include <stdio.h>
#include <string.h>
#include <ctype.h>

void generateCipherSequence(char keyword[], char cipherSequence[]) {
    int keywordLength = strlen(keyword);
    int index = 0,i;
    char ch;

    strcpy(cipherSequence, keyword);

    for (i = 0; i < keywordLength; i++) {
        if (isalpha(keyword[i])) {
            keyword[i] = tolower(keyword[i]);
            cipherSequence[i] = toupper(cipherSequence[i]);
        }
    }

    for ( ch = 'A'; ch <= 'Z'; ch++) {
        if (strchr(keyword, ch) == NULL) {
            cipherSequence[keywordLength + index] = ch;
            index++;
        }
    }
    cipherSequence[keywordLength + index] = '\0';
}

void encryptMonoalphabetic(char plainText[], char cipherSequence[], char cipherText[]) {
    int length = strlen(plainText),i;

    for ( i = 0; i < length; i++) {
        if (isalpha(plainText[i])) {
            int index;
            if (isupper(plainText[i])) {
                index = plainText[i] - 'A';
                cipherText[i] = cipherSequence[index];
            } else {
                index = plainText[i] - 'a';
                cipherText[i] = tolower(cipherSequence[index]);
            }
        } else {
            
            cipherText[i] = plainText[i];
        }
    }
    cipherText[length] = '\0';
}

int main() {
    char keyword[] = "CIPHER";
    char cipherSequence[26];
    char plainText[] = "Hello, World!";
    char cipherText[100];

    printf("Keyword: %s\n", keyword);

    generateCipherSequence(keyword, cipherSequence);
    printf("Cipher Sequence: %s\n", cipherSequence);

    encryptMonoalphabetic(plainText, cipherSequence, cipherText);
    printf("Plain Text: %s\n", plainText);
    printf("Cipher Text: %s\n", cipherText);

    return 0;
}
