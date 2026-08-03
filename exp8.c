#include <stdio.h>
#include <ctype.h>

int main() {

    char plain[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char cipher[]="CIPHERABDFGJKLMNOQSTUVWXYZ";

    char text[100];

    printf("Enter plaintext: ");

    scanf("%[^\n]",text);

    printf("Ciphertext: ");

    for(int i=0;text[i];i++){

        if(isalpha(text[i])){

            char c=toupper(text[i]);

            printf("%c",cipher[c-'A']);

        }
        else
            printf("%c",text[i]);
    }

    return 0;
}
