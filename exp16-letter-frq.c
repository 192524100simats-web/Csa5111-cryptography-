#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Standard English frequency order
const char ENGLISH_FREQ[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

typedef struct {
    char letter;
    int count;
} FreqPair;

int compare_freq(const void *a, const void *b) {
    return ((FreqPair *)b)->count - ((FreqPair *)a)->count;
}

void frequency_attack(const char *ciphertext, int top_n) {
    FreqPair freq[26];
    for (int i = 0; i < 26; i++) {
        freq[i].letter = 'A' + i;
        freq[i].count = 0;
    }

    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            freq[toupper(ciphertext[i]) - 'A'].count++;
        }
    }

    qsort(freq, 26, sizeof(FreqPair), compare_freq);

    printf("\n--- TOP %d POSSIBLE DECRYPTIONS ---\n", top_n);
    for (int shift = 0; shift < top_n && shift < 26; shift++) {
        char map[26];
        for (int i = 0; i < 26; i++) {
            int mapped_idx = (i + shift) % 26;
            map[freq[mapped_idx].letter - 'A'] = ENGLISH_FREQ[i];
        }

        printf("\nRank %d:\n", shift + 1);
        for (int i = 0; i < len; i++) {
            if (isalpha(ciphertext[i])) {
                char base = isupper(ciphertext[i]) ? 'A' : 'a';
                char decrypted = map[toupper(ciphertext[i]) - 'A'];
                printf("%c", isupper(ciphertext[i]) ? decrypted : tolower(decrypted));
            } else {
                printf("%c", ciphertext[i]);
            }
        }
        printf("\n");
    }
}

int main() {
    char ciphertext[1000];
    int top_n;

    printf("Enter Ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    printf("Enter number of top plaintexts to display (e.g., 10): ");
    scanf("%d", &top_n);

    frequency_attack(ciphertext, top_n);
    return 0;
}
