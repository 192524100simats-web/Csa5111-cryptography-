#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define N 26

// English single-letter frequencies (%) in ETAOIN order
double engFreq[N] = {
 8.2,1.5,2.8,4.3,12.7,2.2,2.0,6.1,7.0,0.15,0.77,4.0,2.4,
 6.7,7.5,1.9,0.095,6.0,6.3,9.1,2.8,0.98,2.4,0.15,2.0,0.074
};

char cipher[100000];
int clen;

double scoreKey(int key[26]){
    // key[c] = plaintext letter index for cipher letter c
    int count[26] = {0};
    for(int i=0;i<clen;i++){
        if(isalpha(cipher[i])){
            int c = toupper(cipher[i]) - 'A';
            count[key[c]]++;
        }
    }
    double score = 0;
    for(int i=0;i<26;i++){
        double p = (clen>0)? (100.0*count[i]/clen):0;
        score -= fabs_(p - engFreq[i]);
    }
    return score;
}
double fabs_(double x){ return x<0?-x:x; }

void decryptWith(int key[26], char *out){
    for(int i=0;i<clen;i++){
        if(isalpha(cipher[i])){
            int c = toupper(cipher[i]) - 'A';
            char p = 'A' + key[c];
            out[i] = islower(cipher[i]) ? tolower(p) : p;
        } else out[i] = cipher[i];
    }
    out[clen] = 0;
}

typedef struct { int key[26]; double score; char text[100000]; } Candidate;
Candidate cands[500];
int ncand = 0;

void tryCandidate(int key[26]){
    double s = scoreKey(key);
    char buf[100000];
    decryptWith(key, buf);
    // avoid near-duplicates
    for(int i=0;i<ncand;i++) if(strcmp(cands[i].text, buf)==0) return;
    if(ncand < 500){
        memcpy(cands[ncand].key, key, sizeof(int)*26);
        cands[ncand].score = s;
        strcpy(cands[ncand].text, buf);
        ncand++;
    }
}

int cmp(const void *a, const void *b){
    double d = ((Candidate*)b)->score - ((Candidate*)a)->score;
    return d>0?1:(d<0?-1:0);
}

int main(){
    printf("Enter ciphertext (end with a blank line):\n");
    clen = 0;
    char line[2048];
    while(fgets(line, sizeof(line), stdin)){
        if(strcmp(line, "\n")==0) break;
        strcat(cipher, line);
        clen = strlen(cipher);
    }

    int freqOrder[26], idx[26];
    int count[26] = {0};
    for(int i=0;i<clen;i++)
        if(isalpha(cipher[i])) count[toupper(cipher[i])-'A']++;
    for(int i=0;i<26;i++) idx[i]=i;
    // sort cipher letters by descending frequency
    for(int i=0;i<26;i++)
        for(int j=i+1;j<26;j++)
            if(count[idx[j]] > count[idx[i]]){ int t=idx[i]; idx[i]=idx[j]; idx[j]=t; }

    // baseline mapping: most frequent cipher letter -> 'E', etc (ETAOIN order)
    int etaoin[26] = {4,19,0,14,8,13,18,7,17,3,11,2,20,15,21,5,22,8,24,25,10,7,1,9,6,23}; // rough order, we'll just use rank
    char order[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";
    int baseKey[26];
    for(int r=0;r<26;r++){
        int cLetter = idx[r];
        baseKey[cLetter] = order[r] - 'A';
    }
    tryCandidate(baseKey);

    // hill-climbing with random restarts: try swapping pairs in plaintext-letter assignment
    srand(time(NULL));
    for(int restart=0; restart<60; restart++){
        int key[26]; memcpy(key, baseKey, sizeof(key));
        if(restart>0){
            // randomly perturb by swapping a few output letters
            for(int s=0;s<3;s++){
                int a = rand()%26, b = rand()%26;
                // find cipher letters mapped to plaintext a and b, swap their targets
                for(int c=0;c<26;c++){
                    if(key[c]==a) key[c]=b;
                    else if(key[c]==b) key[c]=a;
                }
            }
        }
        double best = scoreKey(key);
        int improved = 1;
        while(improved){
            improved = 0;
            for(int i=0;i<26 && !improved;i++)
                for(int j=i+1;j<26 && !improved;j++){
                    int test[26]; memcpy(test,key,sizeof(key));
                    // swap plaintext assignment of letters i and j
                    for(int c=0;c<26;c++){
                        if(test[c]==i) test[c]=j;
                        else if(test[c]==j) test[c]=i;
                    }
                    double s = scoreKey(test);
                    if(s > best){ best = s; memcpy(key,test,sizeof(key)); improved = 1; }
                }
        }
        tryCandidate(key);
    }

    qsort(cands, ncand, sizeof(Candidate), cmp);

    int topN;
    printf("\nHow many top candidates to show? ");
    scanf("%d", &topN);
    if(topN > ncand) topN = ncand;

    for(int i=0;i<topN;i++){
        printf("\n--- Candidate #%d (score=%.2f) ---\n%s\n", i+1, cands[i].score, cands[i].text);
    }
    return 0;
}
