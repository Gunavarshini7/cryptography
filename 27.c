#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int modInverse(int e, int phi) {
	int x;
    e = e % phi;
    for ( x = 1; x < phi; x++) {
        if ((e * x) % phi == 1) return x;
    }
    return -1;
}

int modPow(int base, int exponent, int mod) {
    int result = 1;
    base = base % mod;
    while (exponent > 0) {
        if (exponent % 2 == 1) result = (result * base) % mod;
        exponent = exponent >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    // Simplified example; use large primes in real applications
    int p = 68, q = 83;
    int n = p * q;
    int phi = (p - 1) * (q - 1);
    int e = 17; // Choose e such that 1 < e < phi and e is co-prime to phi
    int d = modInverse(e, phi);
    int message = 12; // Example message (as an integer)
    int encrypted = modPow(message, e, n);
    int decrypted = modPow(encrypted, d, n);

    printf("Original: %d\nEncrypted: %d\nDecrypted: %d\n", message, encrypted, decrypted);
    return 0;
}

