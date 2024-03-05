#include <stdio.h>
#include <stdlib.h>

// Function to compute a^b mod p
long long modPow(long long a, long long b, long long p) {
    long long result = 1;
    a = a % p;
    while (b > 0) {
        if (b & 1) result = (result * a) % p;
        b = b >> 1;
        a = (a * a) % p;
    }
    return result;
}

int main() {
    long long p = 23; // Prime number
    long long g = 5;  // Base

    // Alice selects a secret number a, computes g^a mod p
    long long a = 6; // Alice's secret
    long long A = modPow(g, a, p);

    // Bob selects a secret number b, computes g^b mod p
    long long b = 15; // Bob's secret
    long long B = modPow(g, b, p);

    // Exchange and compute the shared secret
    long long secretAlice = modPow(B, a, p);
    long long secretBob = modPow(A, b, p);

    printf("Alice's Shared Secret: %lld\n", secretAlice);
    printf("Bob's Shared Secret: %lld\n", secretBob);

    return 0;
}

