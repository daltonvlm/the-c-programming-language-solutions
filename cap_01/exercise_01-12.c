#include <stdio.h>

#define IN 1        /* inside a word */
#define OUT 0       /* outside a word */

main()
{
    int c, state;

    state = OUT;
    while ((c = getchar()) != EOF) {
        if (' ' == c || '\t' == c || '\n' == c) {
            if (IN == state) {
                putchar('\n');
            }
            state = OUT;
        } else {
            state = IN;
            putchar(c);
        }
    }
}
