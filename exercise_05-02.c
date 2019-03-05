/*
 * Write a getfloat, the floating-point analog of getint. What type does getfloat
 * return as its function value?
 */

#include <stdio.h>
#include <ctype.h>

int getch(void);
void ungetch(int);

/* getint: get next integer from input into *pn */
int getfloat(float *pn)
{
	int c, sign, e;

	while (isspace(c = getch()))	/* skip white space */
		;
	sign = (c == '-') ? -1 : 1;
	if ('+' == c || '-' == c) {
        c = getch();
        if (!isdigit(c) && c != '.') {
            ungetch(c);
            c = sign < 1 ? '-' : '+';
        }
	}
	if (!isdigit(c) && c != '.') {
		ungetch(c);		/* it's not a number */
		return EOF == c ? EOF : 0;
	}
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    e = 1;
	if ('.' == c) 
		for (c = getch(); isdigit(c); c = getch(), e *= 10)
			*pn = 10 * *pn + (c - '0');
	*pn = (*pn * sign) / e;
	ungetch(c);
	return 1;
}
