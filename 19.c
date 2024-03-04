#include <windows.h>
#include <wincrypt.h>
#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 8

void handleError(const char* message) {
    perror(message);
    exit(EXIT_FAILURE);
}

void encrypt_des3_cbc(const char* input, const char* key, const char* iv, char* output) {
    HCRYPTPROV hProv = 0;
    HCRYPTKEY hKey = 0;
    HCRYPTHASH hHash = 0;
    
    if (!CryptAcquireContext(&hProv, NULL, MS_ENH_RSA_AES_PROV, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {
        handleError("Error acquiring crypto context");
    }

    if (!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash)) {
        handleError("Error creating hash object");
    }

    if (!CryptHashData(hHash, (BYTE*)key, strlen(key), 0)) {
        handleError("Error hashing key");
    }

    if (!CryptDeriveKey(hProv, CALG_3DES, hHash, 0, &hKey)) {
        handleError("Error deriving key");
    }

    // Initialize the IV
    BYTE initVector[BLOCK_SIZE];
    memcpy(initVector, iv, BLOCK_SIZE);

    // Set IV for CBC mode
    if (!CryptSetKeyParam(hKey, KP_IV, initVector, 0)) {
        handleError("Error setting IV");
    }

    // Encrypt in CBC mode
    DWORD inputLength = strlen(input) + 1;  // Include the null terminator
    if (!CryptEncrypt(hKey, 0, TRUE, 0, (BYTE*)input, &inputLength, inputLength)) {
        handleError("Error encrypting data");
    }

    // Copy the result to the output buffer
    memcpy(output, input, inputLength);

    CryptReleaseContext(hProv, 0);
    CryptDestroyKey(hKey);
    CryptDestroyHash(hHash);
}

