#include <stdio.h>

#define NCHARS 256

main()
{
    int c, i;
    int histogram[NCHARS];

    for (i = 0; i < NCHARS; i++) {
        histogram[i] = 0;
    }

    while ((c = getchar()) != EOF) {
        histogram[c]++;
    }

    printf("Code\tFrequency\n");
    for (i = 0; i < NCHARS; i++) {
        if (histogram[i] != 0) {
            printf("%3d:\t%6d\n", i, histogram[i]);
        }
    }
}

