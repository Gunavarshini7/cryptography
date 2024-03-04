#include <stdio.h>
#include <string.h>

void hillEncrypt(char *message, int key[2][2]) {
    int len = strlen(message),i,x1,x2,y1,y2;

    // Adjust the length to be even by appending 'x' if necessary
    if (len % 2 != 0) {
        message[len] = 'x';
        message[len + 1] = '\0';
        len++;
    }

    printf("Encryption Process:\n");

    for (i = 0; i < len; i += 2) {
        x1 = message[i] - 'a';
        x2 = message[i + 1] - 'a';

        y1 = (key[0][0] * x1 + key[0][1] * x2) % 26;
        y2 = (key[1][0] * x1 + key[1][1] * x2) % 26;

        printf("Block: %c%c\n", message[i], message[i + 1]);
        printf("Numeric Values: %d %d\n", x1, x2);
        printf("Encrypted Values: %d %d\n", y1, y2);

        printf("\n");
    }

    printf("Encrypted Message: ");
    for (i = 0; i < len; i++) {
        printf("%c", message[i]);
    }
    printf("\n");
}

int main() {
    char message[] = "meet me at the usual place at ten rather than eight o'clock";
    int key[2][2] = {{9, 4}, {5, 7}};

    printf("Original Message: %s\n", message);
    hillEncrypt(message, key);

    return 0;
}
