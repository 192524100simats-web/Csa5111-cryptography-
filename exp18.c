// (paste the DES tables/functions from program 17 above into this file, then add:)

void tripleDesBlock(unsigned char in[8], unsigned char out[8],
                     int sk1[16][48], int sk2[16][48], int sk3[16][48], int encrypt){
    unsigned char t1[8], t2[8];
    if(encrypt){
        desBlock(in, t1, sk1, 0);   // E with K1
        desBlock(t1, t2, sk2, 1);   // D with K2
        desBlock(t2, out, sk3, 0);  // E with K3
    } else {
        desBlock(in, t1, sk3, 1);   // D with K3
        desBlock(t1, t2, sk2, 0);   // E with K2
        desBlock(t2, out, sk1, 1);  // D with K1
    }
}

void xorBlock(unsigned char *a, unsigned char *b, unsigned char *out){
    for(int i=0;i<8;i++) out[i] = a[i]^b[i];
}

int main(){
    unsigned char k1[8], k2[8], k3[8], iv[8];
    printf("Enter K1, K2, K3 (8 chars each) and IV (8 chars):\n");
    scanf("%8s %8s %8s %8s", k1, k2, k3, iv);

    int sk1[16][48], sk2[16][48], sk3[16][48];
    generateSubkeys(k1, sk1, 0);
    generateSubkeys(k2, sk2, 0);
    generateSubkeys(k3, sk3, 0);

    printf("Enter number of 8-byte plaintext blocks: ");
    int n; scanf("%d", &n);
    unsigned char pt[100][8], ct[100][8], prev[8];
    memcpy(prev, iv, 8);

    printf("Enter each 8-char block:\n");
    for(int i=0;i<n;i++){
        scanf("%8s", pt[i]);
        unsigned char x[8];
        xorBlock(pt[i], prev, x);            // CBC: XOR with previous ciphertext (or IV)
        tripleDesBlock(x, ct[i], sk1, sk2, sk3, 1);
        memcpy(prev, ct[i], 8);
    }

    printf("\nCiphertext blocks:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<8;j++) printf("%02X", ct[i][j]);
        printf(" ");
    }

    // decrypt back to verify
    memcpy(prev, iv, 8);
    printf("\n\nDecrypted plaintext:\n");
    for(int i=0;i<n;i++){
        unsigned char d[8], p[8];
        tripleDesBlock(ct[i], d, sk1, sk2, sk3, 0);
        xorBlock(d, prev, p);
        printf("%.8s", p);
        memcpy(prev, ct[i], 8);
    }
    printf("\n");
    return 0;
}
