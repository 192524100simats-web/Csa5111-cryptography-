#include <stdio.h>

int main(){

    printf("Hill Cipher Known Plaintext Attack\n");
    printf("Formula:\n");
    printf("K = C * inverse(P) mod 26\n");

    printf("\nIf enough plaintext-ciphertext pairs are known,\n");
    printf("the key matrix can be recovered.\n");

    return 0;
}
