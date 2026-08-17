#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

/**
 * Problem 15: Frequency Attack on Additive Cipher
 * The additive cipher is a simple shift cipher: C = (P + K) mod 26.
 * We can break it by trying all 26 possible keys and comparing the resulting
 * letter distribution with the expected English letter distribution.
 */

double ENGLISH_FREQS[26] = {
    0.0817, 0.0149, 0.0278, 0.0425, 0.1270, 0.0223, 0.0202, 0.0609,
    0.0697, 0.0015, 0.0077, 0.0403, 0.0241, 0.0675, 0.0751, 0.0193,
    0.0010, 0.0599, 0.0633, 0.0906, 0.0276, 0.0098, 0.0236, 0.0015,
    0.0197, 0.0007
};

typedef struct {
    int key;
    double score;
    char decoded[1000];
} Result;

int compareResults(const void *a, const void *b) {
    Result *r1 = (Result *)a;
    Result *r2 = (Result *)b;
    if (r1->score < r2->score) return -1;
    if (r1->score > r2->score) return 1;
    return 0;
}

double calculateScore(const char *text) {
    int counts[26] = {0};
    int len = 0;
    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            counts[toupper(text[i]) - 'A']++;
            len++;
        }
    }
    if (len == 0) return 1e9;

    double chiSquare = 0;
    for (int i = 0; i < 26; i++) {
        double expected = ENGLISH_FREQS[i] * len;
        chiSquare += pow(counts[i] - expected, 2) / expected;
    }
    return chiSquare;
}

void decrypt(const char *cipher, int key, char *plain) {
    int j = 0;
    for (int i = 0; cipher[i]; i++) {
        if (isalpha(cipher[i])) {
            int c = toupper(cipher[i]) - 'A';
            int p = (c - key + 26) % 26;
            plain[j++] = p + 'A';
        } else {
            plain[j++] = cipher[i];
        }
    }
    plain[j] = '\0';
}

int main() {
    char cipherText[] = "Wkh txlfn eurzq ira mxpsv ryhu wkh odcb grj";
    // (This is "The quick brown fox..." shifted by 3: T(19)->W(22), H(7)->K(10), E(4)->H(7))

    Result results[26];

    for (int k = 0; k < 26; k++) {
        results[k].key = k;
        decrypt(cipherText, k, results[k].decoded);
        results[k].score = calculateScore(results[k].decoded);
    }

    qsort(results, 26, sizeof(Result), compareResults);

    printf("Top 10 possible plaintexts for ciphertext: \"%s\"\n", cipherText);
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < 10; i++) {
        printf("%d. Key %2d | Score: %8.2f | %s\n", i + 1, results[i].key, results[i].score, results[i].decoded);
    }

    return 0;
}
