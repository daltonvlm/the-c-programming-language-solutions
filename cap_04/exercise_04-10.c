/*
 * An alternate organization uses getline to read an entire input line; this makes getch
 * and ungetch unnecessary. Revise the calculator to use this approach.
 */

#include <ctype.h>

#define NUMBER 	'0'		/* signal that a number was found */
#define BUFSIZE 81

char buf[BUFSIZE];
int bufp = 0;

/* getop: get next operator or numeric operand */
int getop(char s[], int len)
{
	int i, c;
	int getline(char[], int);

	if ('\0' == buf[bufp])
		if (0 == getline(buf, BUFSIZE))
			return EOF;
		else
			bufp = 0;

	while ((s[0] = c = buf[bufp++]) == ' ' || c == '\t')
		;
	s[1] = '\0';

	if (!isdigit(c) && c != '.')
		return c;	  	/* not a number */

	i = 0;
	if (isdigit(c))		/* collect integer part */
		while (isdigit(s[++i] = c = buf[bufp++]) && i < len - 1)
				;
	if (i < len - 1 && c == '.')		/* collect fraction part */
		while (isdigit(s[i] = c = buf[bufp++]) && i < len - 1)
			;
	s[i] = '\0';
	bufp--;
	return NUMBER;
}
