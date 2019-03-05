/*
 * Modify getop so that it doesn't need to use ungetch. Hint: use an internal static
 * variable.
 */

#include <stdio.h>
#include <ctype.h>
#include "calc.h"

#define EMPTY '\0'

/* getop: get next operator or numeric operand */
int getop(char s[], int len)
{
	int i, c;
	static int buf = EMPTY;

	c = EMPTY == buf ? getch() : buf;
	buf = EMPTY;

	while ((s[0] = c) == ' ' || c == '\t')
		c = getch();
		;
	s[1] = '\0';
	if (!isdigit(c) && c != '.')
		return c;	  	/* not a number */
	i = 0;
	if (isdigit(c))		/* collect integer part */
		while (isdigit(s[++i] = c = getch()) && i < len - 1)
			;
	if (i < len - 1 && c == '.')		/* collect fraction part */
		while (isdigit(s[++i] = c = getch()) && i < len - 1)
			;
	s[i] = '\0';
	if (c != EOF)
		buf = c;
	return NUMBER;
}
