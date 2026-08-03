#include <stdio.h>

int main(){

    int inv[2][2]={{5,12},{15,25}};

    char cipher[200];

    printf("Enter ciphertext: ");
    scanf("%s",cipher);

    for(int i=0;cipher[i];i+=2){

        int a=cipher[i]-'a';
        int b=cipher[i+1]-'a';

        int p1=(inv[0][0]*a+inv[0][1]*b)%26;
        int p2=(inv[1][0]*a+inv[1][1]*b)%26;

        printf("%c%c",p1+'a',p2+'a');
    }
}
