/*
 * As written, getint treats a + or - not followed by a digit as a valid 
 * representation of zero. Fix it to push such a character back on the 
 * input.
 */

#include <stdio.h>
#include <ctype.h>

int getch(void);
void ungetch(int);

/* getint: get next int from input into *pn */
int getint(int *pn)
{
    int c, sign;

    while (isspace(c = getch()));     /* skip white space */
        ;
    sign = c == '-' ? -1 : 1;
    if (c == '+' || c == '-') {
        c = getch();
        if (!isdigit(c)) {
            ungetch(c);
            c = sign < 0 ? '-' : '+';
        }
    }
    if (!isdigit(c)) {
        ungetch(c);     /* it's not a number */
        return EOF == c ? EOF : 0;
    }
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    ungetch(c);
    return 1;
}
