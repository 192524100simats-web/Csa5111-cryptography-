#include <stdio.h>
#include <ctype.h>

int main(){

    char text[]="sendmoremoney";

    int key[]={9,0,1,7,23,15,21,14,11,11,2,8,9};

    printf("Ciphertext: ");

    for(int i=0;text[i];i++){

        int p=text[i]-'a';

        int c=(p+key[i])%26;

        printf("%c",c+'a');
    }

    printf("\n");

    return 0;
}
