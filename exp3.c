#include <stdio.h>
#include <string.h>
#include <ctype.h>

char matrix[5][5];

void generateMatrix(char key[]) {
    int used[26] = {0};
    int i, j, k = 0;

    used['J' - 'A'] = 1;

    for(i = 0; key[i]; i++) {
        char ch = toupper(key[i]);
        if(ch == 'J') ch = 'I';

        if(ch >= 'A' && ch <= 'Z' && !used[ch-'A']) {
            matrix[k/5][k%5] = ch;
            used[ch-'A'] = 1;
            k++;
        }
    }

    for(i = 0; i < 26; i++) {
        if(!used[i]) {
            matrix[k/5][k%5] = 'A'+i;
            k++;
        }
    }
}

void findPosition(char ch, int *row, int *col) {
    if(ch=='J') ch='I';

    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
            if(matrix[i][j]==ch){
                *row=i;
                *col=j;
                return;
            }
}

int main() {
    char key[30], text[100];

    printf("Enter key: ");
    scanf("%s", key);

    generateMatrix(key);

    printf("\nMatrix:\n");
    for(int i=0;i<5;i++) {
        for(int j=0;j<5;j++)
            printf("%c ", matrix[i][j]);
        printf("\n");
    }

    getchar();

    printf("\nEnter plaintext (even letters): ");
    fgets(text,sizeof(text),stdin);

    printf("Ciphertext: ");

    for(int i=0;text[i] && text[i+1];i+=2) {
        char a=toupper(text[i]);
        char b=toupper(text[i+1]);

        if(a=='\n'||b=='\n') break;

        int r1,c1,r2,c2;
        findPosition(a,&r1,&c1);
        findPosition(b,&r2,&c2);

        if(r1==r2){
            printf("%c%c",matrix[r1][(c1+1)%5],matrix[r2][(c2+1)%5]);
        }
        else if(c1==c2){
            printf("%c%c",matrix[(r1+1)%5][c1],matrix[(r2+1)%5][c2]);
        }
        else{
            printf("%c%c",matrix[r1][c2],matrix[r2][c1]);
        }
    }

    return 0;
}
