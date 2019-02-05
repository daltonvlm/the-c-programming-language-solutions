#include <stdio.h>

#define TABSTOP 4

int isblank(char c);

main()
{
    int c, i, nblanks, left;

    i = 0;
    nblanks = 0;
    while ((c = getchar()) != EOF) {
        if ('\n' == c) {
            i = 0;
            nblanks = 0;
            putchar(c);
        } else if (isblank(c)) {
            nblanks++;
            left = ((i + nblanks) % TABSTOP);
            if (0 == left) {
                putchar('\t');
                i += nblanks;
                nblanks = 0;
            }
        } else {
            i += nblanks + 1;
            for (; nblanks > 0; nblanks--) {
                putchar(' ');
            }
            putchar(c);
        }
    }
    return 0;
}

int isblank(char c)
{
    return ' ' == c;
}
