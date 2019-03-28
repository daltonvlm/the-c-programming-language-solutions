#include <stdio.h>

#define TABSTOP 8

main()
{
    int c, col, nb;

    nb = 0;
    for (col = 1; (c = getchar()) != EOF; col++)
        if (' ' == c) {
            nb++;
            if (col % TABSTOP == 0) {
                nb = 0;
                col += TABSTOP - (col % TABSTOP);
                putchar('\t');
            }
        } else if ('\t' == c) {
            nb = 0;
            col += TABSTOP - (col % TABSTOP);
            putchar('\t');
        } else {
            for (; nb; nb--)
                putchar(' ');
            putchar(c);
            if ('\n' == c)
                col = 0;
        }
}

