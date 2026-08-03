#include <stdio.h>
#include <ctype.h>

int main() {

    char cipher[200];

    printf("Enter ciphertext: ");
    scanf("%s", cipher);

    printf("Plaintext: ");

    for(int i=0; cipher[i]; i++) {

        if(isalpha(cipher[i])) {

            int c=toupper(cipher[i])-'A';

            int p=(9*(c-15+26))%26;

            printf("%c",'A'+p);
        }
    }

    return 0;
}
