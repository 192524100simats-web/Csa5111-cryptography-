#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main() {
    char plaintext[100];
    char key[27];

    printf("Enter substitution key (26 unique letters): ");
    scanf("%s", key);

    getchar();

    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    printf("Ciphertext: ");

    for(int i = 0; plaintext[i] != '\0'; i++) {
        char ch = plaintext[i];

        if(isupper(ch))
            printf("%c", toupper(key[ch-'A']));
        else if(islower(ch))
            printf("%c", tolower(key[ch-'a']));
        else
            printf("%c", ch);
    }

    return 0;
}
