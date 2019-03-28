/*
 * Our getch and ungetch do not handle a push-back EOF correctly. Decide 
 * what their properties ought to be if an EOF is pushed back, then 
 * implement your design.
 */

#include <stdio.h>

#define BUFSIZE	100

/* to handle the EOF properly, buf must be an array of ints, not of chars */
int buf[BUFSIZE];	/* buffer for ungetch */
int bufp = 0;		/* next free position in buf */

int getch(void)	/* get a (possibly pushed back) character */
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}
