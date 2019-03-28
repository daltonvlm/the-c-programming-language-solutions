#include <stdio.h>
#include <ctype.h>

#define NUMBER '0'

int getch(void);
void ungetch(int);

/* getop: get next operator or numeric operand 
 *
 * This is a better version than that provided by the book
 * because it checks for limits of s.
 */
int getop(char s[], int lim)
{
    int i, c;

    if (lim < 2) {
        printf("getop: insufficient storage space (minimum is 2)\n");
        return EOF;
    }

    while ((s[0] = c = getch()) == ' ' ||  c == '\t')
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c;       /* not a number */
    i = 0;
    if (isdigit(c))     /* collect integer part */
        while (isdigit(s[++i] = c = getch()) && i < lim - 1)
            ;
    if (i < lim - 1 && c == '.')       /* collect fraction part */
        while (isdigit(s[++i] = c = getch()) && i < lim - 1)
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}
