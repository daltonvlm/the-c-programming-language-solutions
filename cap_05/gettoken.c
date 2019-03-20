#include <ctype.h>
#include <string.h>
#include "dcl.h"

int skip;

extern int getch(void);
extern void ungetch(int);

/* 
 * This and other programs don't check the limits of the strings, so they 
 * are not "secure". But I decided to follow the book examples and to 
 * concentrate on the topic been teaching at the moment.
 */

int gettoken(void)	/* return next token */
{
	int c;
	char *p = token;

	if (skip) {
		skip = 0;
		return tokentype;
	}

	while ((c = getch()) == ' ' || c == '\t')
		;
	if (c == '(') {
		c = getch();
		ungetch(c);
		if (c  == ')' || name[0] != '\0') {
			for (*p++ = '('; (*p++ = getch()) != ')'; )
				;
			*p = '\0';
			return tokentype = PARENS;
		} else
			return tokentype = '(';
	} else if (c == '[') {
		for (*p++ = c; (*p++ = getch()) != ']'; )
			;
		*p = '\0';
		return tokentype = BRACKETS;
	} else if (isalpha(c)) {
		for (*p++ = c; isalnum(c = getch()); )
			*p++ = c;
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	} else
		return tokentype = c;
}
