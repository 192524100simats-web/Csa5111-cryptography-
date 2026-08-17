#include <stdio.h>
#include <stdint.h>

// DES Shift Schedule for Key Generation
const int SHIFTS[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

// Simulated 56-bit Key Split into two 28-bit Halves C and D
void generate_decryption_keys(uint32_t C, uint32_t D, uint32_t subkeys[16]) {
    uint32_t keys[16];

    // Generate keys K1 to K16 (Left Shifts)
    for (int i = 0; i < 16; i++) {
        C = ((C << SHIFTS[i]) | (C >> (28 - SHIFTS[i]))) & 0x0FFFFFFF;
        D = ((D << SHIFTS[i]) | (D >> (28 - SHIFTS[i]))) & 0x0FFFFFFF;
        keys[i] = (C ^ D); // Simplified 48-bit subkey mock
    }

    // Assign in REVERSE order for Decryption
    for (int i = 0; i < 16; i++) {
        subkeys[i] = keys[15 - i];
    }
}

int main() {
    uint32_t C0 = 0x0FFFFFFE, D0 = 0x0AABBCCD;
    uint32_t decrypt_subkeys[16];

    generate_decryption_keys(C0, D0, decrypt_subkeys);

    printf("DES Decryption Subkeys (K16 down to K1):\n");
    for (int i = 0; i < 16; i++) {
        printf("Decryption Round %2d (K%d): 0x%08X\n", i + 1, 16 - i, decrypt_subkeys[i]);
    }

    return 0;
}
