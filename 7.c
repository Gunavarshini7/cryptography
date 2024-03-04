#include <stdio.h>
#include <string.h>

void decryptSubstitution(char* ciphertext, char* substitutionMap) {
	int i;
    
    for ( i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= '0' && ciphertext[i] <= '9') {
          
            printf("%c", substitutionMap[ciphertext[i] - '0' + 26]);
        } else if (ciphertext[i] >= '(' && ciphertext[i] <= '9') {
         
            printf("%c", substitutionMap[ciphertext[i] - '(' + 36]);
        } else if (ciphertext[i] == ' ') {
         
            printf(" ");
        } else {
           
            printf("%c", substitutionMap[ciphertext[i] - 'A']);
        }
    }

    printf("\n");
}

int main() {
    char ciphertext[] = "7653774882746,8774";

    char substitutionMap[128] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789()*;:[]—";

    char e_guess = 'e';
    char most_frequent_char = 'B';  
    substitutionMap[most_frequent_char - 'A'] = e_guess;

    char t_guess = 't';
    char h_guess = 'h';
    char second_most_frequent_char = 'U';  
    substitutionMap[second_most_frequent_char - 'A'] = t_guess;

    char common_pair_guess = 'm';
   
    substitutionMap[common_pair_guess - 'A'] = h_guess;

    decryptSubstitution(ciphertext, substitutionMap);

    return 0;
}
