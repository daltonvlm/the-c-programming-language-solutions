#include <stdio.h>

#define IN  1   /* inside a word */
#define OUT 0   /* outside a word */

/* count lines, words, and characters in input */
main()
{
    int c, nl, nw, nc, state;

    state = OUT;
    nl = nw = nc = 0;
    while ((c = getchar()) != EOF) {
        ++nc;
        if (' ' == c || '\t' == c || '\n' == c || '\f' == c || '\v' == c) {
            state = OUT;
            if ('\n' == c) {
                ++nl;
            }
        } else if (OUT == state) {
            state = IN;
            ++nw;
        }
    }
    printf("%d %d %d\n", nl, nw, nc);
}
