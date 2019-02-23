/*
 * Suppose that there will never be more than one character of pushback. Modify getch
 * and ungetch accordingly.
 */

#include <stdio.h>

#define EMPTY '\0'

int buf = EMPTY;

int getch(void)	/* get a (possibly pushed back) character */
{
	char c;

	c = EMPTY != buf ? buf : getchar();
	buf = EMPTY;
	return c;
}

void ungetch(int c) /* push character back on input */
{
	if (buf != EMPTY)
		printf("ungetch: too many characters\n");
	else
		buf = c;
}
