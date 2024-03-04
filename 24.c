#include <stdio.h>

// Function to find the greatest common divisor (GCD) using Euclid's algorithm
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// Function to find the multiplicative inverse using the extended Euclidean algorithm
int modInverse(int e, int phi) {
    int m0 = phi, t, q;
    int x0 = 0, x1 = 1;

    if (phi == 1) return 0;

    while (e > 1) {
        q = e / phi;
        t = phi;
        phi = e % phi, e = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0) x1 += m0;

    return x1;
}

int main() {
    int e = 31;
    int n = 3599;

    // Trial-and-error to find p and q
    int p, q;
    for (p = 2; p < n; p++) {
        if (n % p == 0) {
            q = n / p;
            break;
        }
    }

    // Compute phi(n)
    int phi_n = (p - 1) * (q - 1);

    // Find the private key using the extended Euclidean algorithm
    int d = modInverse(e, phi_n);

    printf("p = %d\n", p);
    printf("q = %d\n", q);
    printf("Private Key (d) = %d\n", d);

    return 0;
}

