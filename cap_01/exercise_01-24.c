/*
 * Write a program to check a C program for rudimentary syntax errors like 
 * unbalanced parentheses, brackets, and braces. Don't forget about 
 * quotes, both single and double, escape sequences, and comments. (This 
 * program is hard if you do it in full generality.)
 */

#include <stdio.h>

int rcomment(int c);
void incomment(int c, int d);
void inquotes(int c);
void parsing_error(char *msg);

main()
{
	int c, parenthesis, brackets, braces;

	parenthesis = brackets = braces = 0;

	while ((c = getchar()) != EOF) {
		c = rcomment(c);
		if ('(' == c) {
			parenthesis++;
		} else if (')' == c) {
			parenthesis--;
		} else if ('[' == c) {
			brackets++;
		} else if (']' == c) {
			brackets--;
		} else if ('{' == c) {
			braces++;
		} else if ('}' == c) {
			braces--;
		}
	}

	if (parenthesis) {
		printf("Syntax error: unbalanced parenthesis (%d)\n", parenthesis);
	}
	if (brackets) {
		printf("Syntax error: unbalanced brackets (%d)\n", brackets);
	}
	if (braces) {
		printf("Syntax error: unbalanced braces (%d)\n", braces);
	}
	return 0;
}

int rcomment(int c)
{
	int d;

	if ('/' == c) {
		d = getchar();
		if ('*' == d) {
			incomment(c, d);
		} else {
			return rcomment(d);	
		}
	} else if ('\'' == c || '"' == c) {
		inquotes(c);
	}
	return c;
}

void incomment(int c, int d)
{
	int search;

	search = 1;
	while (search) {
		if ('*' == c && '/' == d) {
			search = 0;
		} else {
			c = d;
			d = getchar();
			if (EOF == d) {
				parsing_error("end of file with unclosed comment");
				search = 0;
			} else if ('/' == c && '*' == d) {
				parsing_error("nested comments");
				search = 0;
			}
		}
	}
}

void inquotes(int c)
{
	int d, search;

	search = 1;
	while (search) {
		if ((d = getchar()) == EOF) {
			parsing_error("end of file whith unclosed quote");
			search = 0;
		} else if (d == c) {
			search = 0;
		} else if ('\\' == d) {
			d = getchar();
		}
	}
}

void parsing_error(char *msg)
{
	printf("\nParsing error: %s\n", msg);
}
