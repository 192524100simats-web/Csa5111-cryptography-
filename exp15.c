#include <stdio.h>
#include <string.h>
#include <ctype.h>

void decrypt(char text[], int key){

    for(int i=0;text[i];i++){

        if(isalpha(text[i])){

            char c=tolower(text[i]);

            c=((c-'a'-key+26)%26)+'a';

            printf("%c",c);

        }else{

            printf("%c",text[i]);

        }

    }

}

int main(){

    char cipher[200];

    printf("Enter ciphertext: ");
    fgets(cipher,200,stdin);

    printf("\nTop 10 possible plaintexts:\n\n");

    for(int key=0;key<10;key++){

        printf("Key %d : ",key);

        decrypt(cipher,key);

        printf("\n");

    }

    return 0;
}
