#include <stdio.h>
#include <string.h>
// (paste DES tables/functions from program 17 here for a real block cipher,
//  or use this simplified XOR-based "toy cipher" to focus purely on the propagation logic:)

void toyEncrypt(unsigned char *in, unsigned char *out, unsigned char *key){
    for(int i=0;i<8;i++) out[i] = in[i] ^ key[i] ^ 0xA5; // stand-in invertible block cipher
}
void toyDecrypt(unsigned char *in, unsigned char *out, unsigned char *key){
    for(int i=0;i<8;i++) out[i] = in[i] ^ key[i] ^ 0xA5; // self-inverse here
}

void xorBlock(unsigned char *a, unsigned char *b, unsigned char *out){
    for(int i=0;i<8;i++) out[i]=a[i]^b[i];
}

int main(){
    unsigned char key[8]="SECRETKY";
    unsigned char pt[4][8], ct[4][8], iv[8]="INITVECT", prev[8];
    int n=4;

    printf("Enter 4 plaintext blocks (8 chars each):\n");
    for(int i=0;i<n;i++) scanf("%8s", pt[i]);

    // --- ECB encrypt ---
    unsigned char ecb_ct[4][8];
    for(int i=0;i<n;i++) toyEncrypt(pt[i], ecb_ct[i], key);

    // --- CBC encrypt ---
    memcpy(prev, iv, 8);
    for(int i=0;i<n;i++){
        unsigned char x[8];
        xorBlock(pt[i], prev, x);
        toyEncrypt(x, ct[i], key);
        memcpy(prev, ct[i], 8);
    }

    printf("\nIntroducing a transmission error: flipping a bit in C1...\n");
    ecb_ct[0][0] ^= 0x01;
    ct[0][0] ^= 0x01;

    // --- ECB decrypt with error ---
    printf("\nECB decrypted (error in C1):\n");
    for(int i=0;i<n;i++){
        unsigned char d[8];
        toyDecrypt(ecb_ct[i], d, key);
        printf("P%d: %.8s\n", i+1, d);
    }

    // --- CBC decrypt with error ---
    printf("\nCBC decrypted (error in C1):\n");
    memcpy(prev, iv, 8);
    for(int i=0;i<n;i++){
        unsigned char d[8], p[8];
        toyDecrypt(ct[i], d, key);
        xorBlock(d, prev, p);
        printf("P%d: %.8s\n", i+1, p);
        memcpy(prev, ct[i], 8);
    }
    return 0;
}
