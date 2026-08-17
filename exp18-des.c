#include <stdio.h>
#include <stdint.h>

void verify_des_subkey_disjoint_property(uint32_t C, uint32_t D) {
    printf("Simulating DES Subkey Generation Property:\n\n");

    for (int round = 1; round <= 16; round++) {
        // Shift C and D independently
        C = ((C << 1) | (C >> 27)) & 0x0FFFFFFF;
        D = ((D << 1) | (D >> 27)) & 0x0FFFFFFF;

        // Subkey part 1 (24 bits) comes ONLY from 28-bit C
        uint32_t subkey_part1 = C & 0x00FFFFFF; 

        // Subkey part 2 (24 bits) comes ONLY from 28-bit D
        uint32_t subkey_part2 = D & 0x00FFFFFF; 

        printf("Round %2d Subkey: [Part1 (from C): 0x%06X] | [Part2 (from D): 0x%06X]\n", 
               round, subkey_part1, subkey_part2);
    }
}

int main() {
    uint32_t C0 = 0x0F0F0F0F & 0x0FFFFFFF; // 28-bit left block
    uint32_t D0 = 0x0A5A5A5A & 0x0FFFFFFF; // 28-bit right block

    verify_des_subkey_disjoint_property(C0, D0);
    return 0;
}
