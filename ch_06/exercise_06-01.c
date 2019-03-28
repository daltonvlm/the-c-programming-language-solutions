/*
 * Our version of getword does not properly handle underscores, string 
 * constants, comments, or preprocessor control lines. Write a better 
 * version.
 */

#include <stdio.h>
#include <ctype.h>

extern int getch(void);
extern void ungetch(int);

void readstring(char *, int, char);
void readcomment(char *, int);
void readdirective(char *, int);

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
	int c;
	char *w = word;

	while (isspace(c = getch()) || '_' == c)
		;
	if (!isalpha(c)) {
		switch (c) {
			case '"':
			case '\'':
				readstring(word, lim, c);
				break;
			case '/':
				c = getch();
				if ('*' == c)
					readcomment(word, lim);
				else {
					ungetch(c);
					c = '/';
				}
				break;
			case '#':
				readdirective(word, lim);
				break;
			default:
				*w++ = c;
				*w = '\0';
				break;
		}
		return c;
	}
	for (*w = c; --lim > 0 && isalnum(*++w = getch()); )
		;
	ungetch(*w);
	*w = '\0';
	return c;
}

void readstring(char *word, int lim, char quote)
{
	char *w = word;

	for (*w++ = quote; --lim > 0 && (*w = getch()) != EOF; w++)
		if (quote == *w) {
			w++;
			break;
		} else if ('\\' == *w)
			if (--lim)
				*++w = getch();
	*w = '\0';
}

void readcomment(char *word, int lim)
{
	int c;
	char *w = word;

	c = *w++ = '/';
	--lim;
	for (*w++ = '*'; --lim > 0 && (*w = getch()) != EOF; w++) {
		if ('/' == *w && '*' == c) {
			w++;
			break;
		}
		c = *w;
	}
	*w = '\0';
}

void readdirective(char *word, int lim)
{
	char *w = word;

	for (*w++ = '#'; --lim > 0 && (*w = getch()) != EOF && *w != '\n'; w++)
		;
	*w = '\0';
}
