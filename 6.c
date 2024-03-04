
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main() {
    char ciphertext[1000];
    int letter_counts[26] = {0};
    int i, most_frequent, second_most_frequent;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);

    for (i = 0; i < strlen(ciphertext); i++) {
        ciphertext[i] = toupper(ciphertext[i]);
        if (!isalpha(ciphertext[i])) {
            ciphertext[i] = ' ';
        }
    }

    for (i = 0; i < strlen(ciphertext); i++) {
        if (isalpha(ciphertext[i])) {
            letter_counts[ciphertext[i] - 'A']++;
        }
    }

    most_frequent = 0;
    second_most_frequent = 0;
    for (i = 0; i < 26; i++) {
        if (letter_counts[i] > letter_counts[most_frequent]) {
            second_most_frequent = most_frequent;
            most_frequent = i;
        } else if (letter_counts[i] > letter_counts[second_most_frequent] && i != most_frequent) {
            second_most_frequent = i;
        }
    }

    char replacement1 = 'E';
    char replacement2 = 'T';

    for (i = 0; i < strlen(ciphertext); i++) {
        if (ciphertext[i] == 'B') {
            ciphertext[i] = replacement1;
        } else if (ciphertext[i] == 'U') {
            ciphertext[i] = replacement2;
        }
    }

    int key_a = (replacement1 - 'E' + 26) % 26;
    int key_b = (letter_counts[replacement1 - 'A'] * key_a) % 26;

    char decrypted_text[1000];
    for (i = 0; i < strlen(ciphertext); i++) {
        if (isalpha(ciphertext[i])) {
            int original_index = (ciphertext[i] - 'A' - key_b + 26) % 26;
            decrypted_text[i] = 'A' + original_index;
        } else {
            decrypted_text[i] = ciphertext[i];
        }
    }

    printf("Decrypted Text: %s\n", decrypted_text);

    return 0;
}
