#include <stdio.h>

#define TABSTOP 4

main()
{
    int i, j, c, left;

    i = 0;
    while ((c = getchar()) != EOF) {
        if ('\t' == c) {
            left = TABSTOP - (i % TABSTOP);
            for (j = 0; j < left; j++) {
                putchar(' ');
            }
            i += left;
        } else {
            if ('\n' != c) {
                i++;
            } else {
                i = 0;
            }
            putchar(c);
        }
    }
    return 0;
}
