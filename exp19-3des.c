#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 8

// Basic XOR cipher block function representing 3DES block processing
void triple_des_encrypt_block(const unsigned char *in, unsigned char *out, const char *key) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        out[i] = in[i] ^ key[i % 24]; // Simple mock of 3DES block pass
    }
}

void cbc_3des_encrypt(const unsigned char *plaintext, int len, unsigned char *ciphertext, 
                      const unsigned char *iv, const char *key) {
    unsigned char prev_block[BLOCK_SIZE];
    memcpy(prev_block, iv, BLOCK_SIZE);

    for (int i = 0; i < len; i += BLOCK_SIZE) {
        unsigned char xor_block[BLOCK_SIZE];

        // CBC XOR step: P_i ^ C_{i-1}
        for (int j = 0; j < BLOCK_SIZE; j++) {
            xor_block[j] = plaintext[i + j] ^ prev_block[j];
        }

        // Encrypt step
        triple_des_encrypt_block(xor_block, &ciphertext[i], key);

        // Save output for next block chaining
        memcpy(prev_block, &ciphertext[i], BLOCK_SIZE);
    }
}

int main() {
    unsigned char plaintext[16] = "SecretData123456"; // 2 blocks of 8 bytes
    unsigned char ciphertext[16];
    unsigned char iv[8] = "INITVEC1";
    char key[24] = "123456789012345678901234";

    cbc_3des_encrypt(plaintext, 16, ciphertext, iv, key);

    printf("3DES-CBC Ciphertext (Hex):\n");
    for (int i = 0; i < 16; i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");

    return 0;
}
