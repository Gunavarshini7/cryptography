#include <stdio.h>
#include <stdlib.h>

// Function to compute the Greatest Common Divisor (GCD) using the Euclidean algorithm
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main() {
    long long n; // The product of p and q
    long long block; // The block which is suspected to have a common factor with n
    
    // Assuming n and the block are given
    printf("Enter n (pq): ");
    scanf("%lld", &n);
    
    printf("Enter the block: ");
    scanf("%lld", &block);
    
    // Find and print the GCD
    long long factor = gcd(n, block);
    if (factor > 1) {
        printf("Found a non-trivial common factor of n and the block: %lld\n", factor);
        printf("This factor can potentially be used to factorize n and break the RSA encryption.\n");
    } else {
        printf("No non-trivial common factor found between n and the block.\n");
    }

    return 0;
}

