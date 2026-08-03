#include <stdio.h>
#include <math.h>

int main() {

    double log2Fact = 0;

    for(int i=2;i<=25;i++)
        log2Fact += log(i);

    printf("Approximate key space = 2^%.2f\n",log2Fact);

    double effective = log2Fact - 2*log(120);

    printf("Effective unique key space = 2^%.2f\n",effective);

    return 0;
}
