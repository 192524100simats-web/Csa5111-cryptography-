#include <stdio.h>
#include <ctype.h>

int main() {
    char text[100];
    int a, b;

    printf("Enter plaintext: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter value of a: ");
    scanf("%d", &a);

    printf("Enter value of b: ");
    scanf("%d", &b);

    printf("Ciphertext: ");

    for(int i=0;text[i]!='\0';i++) {
        char ch=text[i];

        if(isupper(ch)) {
            int p=ch-'A';
            printf("%c", ((a*p+b)%26)+'A');
        }
        else if(islower(ch)) {
            int p=ch-'a';
            printf("%c", ((a*p+b)%26)+'a');
        }
        else
            printf("%c", ch);
    }

    return 0;
}
