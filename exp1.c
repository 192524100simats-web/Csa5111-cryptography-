#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main() {
    char text[100];
    int key, i;

    printf("Enter plaintext: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter key (1-25): ");
    scanf("%d", &key);

    printf("Encrypted text: ");

    for(i = 0; text[i] != '\0'; i++) {
        char ch = text[i];

        if(isupper(ch))
            printf("%c", (ch - 'A' + key) % 26 + 'A');
        else if(islower(ch))
            printf("%c", (ch - 'a' + key) % 26 + 'a');
        else
            printf("%c", ch);
    }

    return 0;
}
