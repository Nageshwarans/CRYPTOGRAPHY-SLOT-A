#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BLOCK_SIZE 16

// Function prototypes
void ecb_encrypt(unsigned char *input, unsigned char *output, int length, unsigned char *key);
void ecb_decrypt(unsigned char *input, unsigned char *output, int length, unsigned char *key);
void cbc_encrypt(unsigned char *input, unsigned char *output, int length, unsigned char *key, unsigned char *iv);
void cbc_decrypt(unsigned char *input, unsigned char *output, int length, unsigned char *key, unsigned char *iv);
void cfb_encrypt(unsigned char *input, unsigned char *output, int length, unsigned char *key, unsigned char *iv);
void cfb_decrypt(unsigned char *input, unsigned char *output, int length, unsigned char *key, unsigned char *iv);

// ECB mode encryption
void ecb_encrypt(unsigned char *input, unsigned char *output, int length, unsigned char *key) {
    // Perform ECB encryption here
    // Implement your ECB encryption algorithm here
}

// ECB mode decryption
void ecb_decrypt(unsigned char *input, unsigned char *output, int length, unsigned char *key) {
    // Perform ECB decryption here
    // Implement your ECB decryption algorithm here
}

// CBC mode encryption
void cbc_encrypt(unsigned char *input, unsigned char *output, int length, unsigned char *key, unsigned char *iv) {
    unsigned char temp_iv[BLOCK_SIZE];
    memcpy(temp_iv, iv, BLOCK_SIZE);

    for (int i = 0; i < length; i += BLOCK_SIZE) {
        // XOR the plaintext block with the IV
        for (int j = 0; j < BLOCK_SIZE; j++) {
            input[i + j] ^= temp_iv[j];
        }
        // Perform encryption
        ecb_encrypt(input + i, output + i, BLOCK_SIZE, key);
        // Update IV with the encrypted block
        memcpy(temp_iv, output + i, BLOCK_SIZE);
    }
}

// CBC mode decryption
void cbc_decrypt(unsigned char *input, unsigned char *output, int length, unsigned char *key, unsigned char *iv) {
    unsigned char temp_iv[BLOCK_SIZE];
    memcpy(temp_iv, iv, BLOCK_SIZE);

    for (int i = 0; i < length; i += BLOCK_SIZE) {
        // Save a copy of the ciphertext block
        unsigned char temp_input[BLOCK_SIZE];
        memcpy(temp_input, input + i, BLOCK_SIZE);
        // Perform decryption
        ecb_decrypt(input + i, output + i, BLOCK_SIZE, key);
        // XOR the decrypted block with the IV (or previous ciphertext block)
        for (int j = 0; j < BLOCK_SIZE; j++) {
            output[i + j] ^= temp_iv[j];
        }
        // Update IV with the ciphertext block
        memcpy(temp_iv, temp_input, BLOCK_SIZE);
    }
}

// CFB mode encryption
void cfb_encrypt(unsigned char *input, unsigned char *output, int length, unsigned char *key, unsigned char *iv) {
    unsigned char temp_iv[BLOCK_SIZE];
    memcpy(temp_iv, iv, BLOCK_SIZE);

    for (int i = 0; i < length; i += BLOCK_SIZE) {
        // Perform encryption
        ecb_encrypt(temp_iv, output + i, BLOCK_SIZE, key);
        // XOR the plaintext block with the encrypted IV
        for (int j = 0; j < BLOCK_SIZE; j++) {
            output[i + j] ^= input[i + j];
        }
        // Update IV with the ciphertext block
        memcpy(temp_iv, output + i, BLOCK_SIZE);
    }
}

// CFB mode decryption
void cfb_decrypt(unsigned char *input, unsigned char *output, int length, unsigned char *key, unsigned char *iv) {
    unsigned char temp_iv[BLOCK_SIZE];
    memcpy(temp_iv, iv, BLOCK_SIZE);

    for (int i = 0; i < length; i += BLOCK_SIZE) {
        // Perform encryption
        ecb_encrypt(temp_iv, output + i, BLOCK_SIZE, key);
        // XOR the ciphertext block with the encrypted IV
        for (int j = 0; j < BLOCK_SIZE; j++) {
            output[i + j] = input[i + j] ^ output[i + j];
        }
        // Update IV with the ciphertext block
        memcpy(temp_iv, input + i, BLOCK_SIZE);
    }
}

int main() {
    unsigned char plaintext[] = "This is a plaintext to be encrypted with padding.";
    unsigned char key[] = "secretkey1234567"; // 128-bit key
    unsigned char iv[] = "initializationvec"; // Initialization vector (IV)

    int len = strlen((char *)plaintext);
    int padded_len = (len % BLOCK_SIZE == 0) ? len + BLOCK_SIZE : ((len / BLOCK_SIZE) + 1) * BLOCK_SIZE;
    unsigned char padded_plaintext[padded_len];

    // Pad the plaintext
    memcpy(padded_plaintext, plaintext, len);
    padded_plaintext[len] = 0x80; // Padding starts with 0x80
    for (int i = len + 1; i < padded_len; i++) {
        padded_plaintext[i] = 0x00; // Remaining bytes are filled with 0x00
    }

    unsigned char encrypted_ecb[padded_len];
    unsigned char decrypted_ecb[padded_len];
    unsigned char encrypted_cbc[padded_len];
    unsigned char decrypted_cbc[padded_len];
    unsigned char encrypted_cfb[padded_len];
    unsigned char decrypted_cfb[padded_len];

    // ECB mode
    ecb_encrypt(padded_plaintext, encrypted_ecb, padded_len, key);
    ecb_decrypt(encrypted_ecb, decrypted_ecb, padded_len, key);

    // CBC mode
    cbc_encrypt(padded_plaintext, encrypted_cbc, padded_len, key, iv);
    cbc_decrypt(encrypted_cbc, decrypted_cbc, padded_len, key, iv);

    // CFB mode
    cfb_encrypt(padded_plaintext, encrypted_cfb, padded_len, key, iv);
    cfb_decrypt(encrypted_cfb, decrypted_cfb, padded_len, key, iv);

    // Output results
    printf("Original plaintext: %s\n", plaintext);
    printf("ECB encrypted: %s\n", encrypted_ecb);
    printf("ECB decrypted: %s\n", decrypted_ecb);
    printf("CBC encrypted: %s\n", encrypted_cbc);
    printf("CBC decrypted: %s\n", decrypted_cbc);
    printf("CFB encrypted: %s\n", encrypted_cfb);
    printf("CFB decrypted: %s\n", decrypted_cfb);

    return 0;
}