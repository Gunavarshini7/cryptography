#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Define large prime numbers p and q for simplicity
#define DSA_P 23
#define DSA_Q 11
#define DSA_G 2

typedef struct {
    int x; // Private key
    int y; // Public key
} DSAKey;

typedef struct {
    int r;
    int s;
} DSASignature;

int mod_exp(int base, int exponent, int modulus) {
    int result = 1;
    base = base % modulus;

    while (exponent > 0) {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;

        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }

    return result;
}

int mod_inverse(int a, int m) {
	int x;
    for (x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // Inverse doesn't exist
}

void generate_dsa_key(DSAKey *dsa_key) {
    srand(time(NULL));

    // Choose a private key x randomly
    dsa_key->x = rand() % DSA_Q;

    // Calculate the corresponding public key y
    dsa_key->y = mod_exp(DSA_G, dsa_key->x, DSA_P);
}

DSASignature sign_message(const char *message, DSAKey *dsa_key) {
    DSASignature signature;
    int i;

    // Simulate SHA-256 hash
    unsigned int hash = 0;
    for (i = 0; message[i] != '\0'; i++) {
        hash = (hash * 256 + message[i]) % DSA_Q;
    }

    // Choose a random value k
    int k = rand() % DSA_Q;

    // Calculate r = (g^k mod p) mod q
    signature.r = mod_exp(DSA_G, k, DSA_P) % DSA_Q;

    // Calculate s = k^(-1) * (hash + x*r) mod q
    int k_inverse = mod_inverse(k, DSA_Q);
    if (k_inverse == -1) {
        printf("Error: Inverse of k doesn't exist.\n");
        exit(EXIT_FAILURE);
    }

    signature.s = (k_inverse * (hash + dsa_key->x * signature.r)) % DSA_Q;

    return signature;
}

int verify_signature(const char *message, DSASignature *signature, DSAKey *dsa_key) {
    // Simulate SHA-256 hash
    int i;
    unsigned int hash = 0;
    for ( i = 0; message[i] != '\0'; i++) {
        hash = (hash * 256 + message[i]) % DSA_Q;
    }

    // Calculate w = s^(-1) mod q
    int w = mod_inverse(signature->s, DSA_Q);
    if (w == -1) {
        printf("Error: Inverse of s doesn't exist.\n");
        exit(EXIT_FAILURE);
    }

    // Calculate u1 = (hash * w) mod q
    int u1 = (hash * w) % DSA_Q;

    // Calculate u2 = (r * w) mod q
    int u2 = (signature->r * w) % DSA_Q;

    // Calculate v = ((g^u1 * y^u2) mod p) mod q
    int v1 = mod_exp(DSA_G, u1, DSA_P);
    int v2 = mod_exp(dsa_key->y, u2, DSA_P);
    int v = (v1 * v2) % DSA_P % DSA_Q;

    return (v == signature->r) ? 1 : 0;
}

int main() {
    DSAKey dsa_key;
    generate_dsa_key(&dsa_key);

    const char *message = "Hello, DSA!";

    printf("Message: %s\n", message);

    DSASignature signature = sign_message(message, &dsa_key);

    printf("DSA Signature:\n");
    printf("r: %d\n", signature.r);
    printf("s: %d\n", signature.s);

    int is_verified = verify_signature(message, &signature, &dsa_key);

    if (is_verified) {
        printf("Signature verification successful\n");
    } else {
        printf("Signature verification failed\n");
    }

    return 0;
}

