#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int hasModularInverse(int a, int m) {
    return gcd(a, m) == 1;
}

int main() {
    int a, b;

    printf("Enter the value of a: ");
    scanf("%d", &a);
    printf("Enter the value of b: ");
    scanf("%d", &b);

    if (a < 0 || a >= 26) {
        printf("Invalid value of a. It should be in the range [0, 25].\n");
        return 1;
    }

    if (!hasModularInverse(a, 26)) {
        printf("Invalid value of a. It should have a modular inverse modulo 26.\n");
        return 1;
    }

    printf("Valid values of a and b for the affine Caesar cipher.\n");

    return 0;
}
