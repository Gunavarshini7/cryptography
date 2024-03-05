#include <stdio.h>
#include <stdlib.h>

// Function prototypes
int gcd(int a, int b);
int modInverse(int e, int phi);
int modPow(int base, int exponent, int mod);

int main() {
    // Warning: These are small primes for demonstration. Real RSA uses much larger primes.
    int p = 61;
    int q = 53;
    int n = p * q;
    int phi = (p - 1) * (q - 1);
    int e = 17; // e must be co-prime to phi and 1 < e < phi
    int d = modInverse(e, phi);

    if (d == -1) {
        printf("No modular inverse found. Exiting.\n");
        return 1;
    }

    // Example encryption and decryption
    int message = 42; // The original message to be encrypted
    int encrypted = modPow(message, e, n);
    int decrypted = modPow(encrypted, d, n);

    printf("Original message: %d\n", message);
    printf("Encrypted message: %d\n", encrypted);
    printf("Decrypted message: %d\n", decrypted);

    return 0;
}

// Function to compute the greatest common divisor (Euclidean algorithm)
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to compute the modular inverse
int modInverse(int e, int phi) {
	int x;
    e = e % phi;
    for ( x = 1; x < phi; x++) {
        if ((e * x) % phi == 1)
            return x;
    }
    return -1;
}

// Function to compute base^exponent % mod
int modPow(int base, int exponent, int mod) {
    int result = 1;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % mod;
        }
        exponent = exponent >> 1;
        base = (base * base) % mod;
    }
    return result;
}

