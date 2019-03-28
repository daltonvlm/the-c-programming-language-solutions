/*
 * Implement a simple version of the #define processor (i.e., no arguments)
 * suitable for use with C programs, based on the routines of this section.
 * You may also find getch and ungetch helpful.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 81

struct nlist {
	struct nlist *next;
	char *name;
	char *defn;
};

extern struct nlist *install(char *, char *);
extern void uninstall(char *);
extern struct nlist *lookup(char *);
extern int getch(void);
extern void ungetch(int);

int getword(char *, int);
int parsequotes(char c);
int parsecomment();
int parsedirective(char *, int);

main()
{
	int c, parse;
	char word[MAXWORD];
	struct nlist *np = NULL;

	parse = 1; 
	while (parse) {
		while (isspace(c = getch()))
			putchar(c);
		if (isalpha(c)) {
			ungetch(c);
			if (!getword(word, MAXWORD))
				return 1;
			if ((np = lookup(word)) != NULL)
				strcpy(word, np->defn);
			printf("%s", word);
		} else {
			switch (c) {
				case EOF:
					parse = 0;
					break;
				case '"':
				case '\'':
					if (!parsequotes(c))
						return 1;
					break;
				case '#':
					if (!parsedirective(word, MAXWORD))
						return 1;
					break;
				case '/':
					if ('*' ==  (c = getch())) {
						if (!parsecomment())
							return 1;
					} else {
						ungetch(c);
						putchar('/');
					}
					break;
				default:
					putchar(c);
					break;
			}
		}
	}
	return 0;
}

/* 
 * getword: 
 * 		if the first character of input is alphabetic, stores a token in
 * 		word until a non alphanumeric one is found. Else, stores the first
 * 		character of input.
 * 		Returns 1 if a token is read, 0 otherwise.
 */
int getword(char *word, int n)
{
	char *p = word;

	while (isspace(*p = getch()))
		;
	n--;
	if (!isalpha(*p)) {
		*++p = '\0';
		return 0;
	}
	while (isalnum(*++p = getch()) && --n > 0)
		;
	ungetch(*p);
	*p = '\0';
	return 1;
}

int parsequotes(char c)
{
	int d;

	putchar(c);
	while ((d = getch()) != EOF && d != c) {
		putchar(d);
		if ('\\' == d)
			putchar(d = getch());
	}
	if (d == c) {
		putchar(d);
		return 1;
	}
	return 0;
}

int parsecomment()
{
	int b, c;

	for (b = '\0'; (c = getch()) != EOF; b = c)
		if ('*' == b && '/' == c)
			return 1;
	return 0;
}

int parsedirective(char *word, int n)
{
	int i;
	char name[MAXWORD];
	char defn[MAXWORD];
	char *p;

	if (!getword(word, n))
		return 0;

	if (0 == strcmp(word, "define")) {
		if (!getword(name, MAXWORD))
			return 0;
		i = MAXWORD;
		p = defn;
		while (isspace(*p = getch()))
			;
		i--;
		while (!isspace(*++p = getch()) && --i > 0)
			;
		ungetch(*p);
		*p = '\0';
		if (!install(name, defn))
			return 0;
	} else if (0 == strcmp(word, "undef")) {
		if (!getword(name, MAXWORD))
			return 0;
		uninstall(name);
	} else {
		putchar('#');
		for (i = strlen(word) - 1; i >= 0; i--)
			ungetch(word[i]);
	}
	return 1;
}
