#include <stdio.h>

int main() {

    char text[1000];

    int freq[256]={0};

    printf("Enter ciphertext:\n");

    fgets(text,sizeof(text),stdin);

    for(int i=0;text[i];i++)
        freq[(unsigned char)text[i]]++;

    printf("\nCharacter Frequencies\n\n");

    for(int i=0;i<256;i++)
        if(freq[i]>0)
            printf("%c : %d\n",i,freq[i]);

    return 0;
}
