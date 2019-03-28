/*
 * Write a program to remove all comments from a C program. Don't forget to
 * handle quoted strings and character constants properly. C comments do 
 * not nest.
 */

#include <stdio.h>

void rcomment(int c);
void incomment(int c, int d);
void inquotes(int c);
void parsing_error(char *msg);

main()
{
	int c;

	while ((c = getchar()) != EOF) {
		rcomment(c);
	}
	return 0;
}

void rcomment(int c)
{
	int d;

	if ('/' == c) {
		d = getchar();
		if ('*' == d) {
			incomment(c, d);
		} else {
			putchar(c);
			rcomment(d);
		}
	} else if ('\'' == c || '"' == c) {
		inquotes(c);
	} else {
		putchar(c);
	}
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
	putchar(c);
	while (search) {
		if ((d = getchar()) == EOF) {
			parsing_error("end of file whith unclosed quote");
			search = 0;
		} else {
			putchar(d);
			if (d == c) {
				search = 0;
			} else if ('\\' == d) {
				if ((d = getchar()) != EOF) {
					putchar(d);
				}
			}
		}
	}
}

void parsing_error(char *msg)
{
	printf("Parsing error: %s\n", msg);
}
