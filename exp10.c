#include <stdio.h>

int main() {

    char matrix[5][5]={
        {'M','F','H','I','K'},
        {'U','N','O','P','Q'},
        {'Z','V','W','X','Y'},
        {'E','L','A','R','G'},
        {'D','S','T','B','C'}
    };

    printf("Playfair Matrix:\n\n");

    for(int i=0;i<5;i++){

        for(int j=0;j<5;j++)
            printf("%c ",matrix[i][j]);

        printf("\n");
    }

    printf("\nEncryption Rules\n");
    printf("1. Same row -> move right\n");
    printf("2. Same column -> move down\n");
    printf("3. Rectangle -> swap columns\n");

    return 0;
}
