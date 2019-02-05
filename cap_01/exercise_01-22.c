#include <stdio.h>

#define MAXCOLUMN 10
#define TABSTOP	  5

int expand(char line[], int i, int lim);
void print(char line[], int lim);
int fold(char line[], int lim);
int shift(char line[], int lim);

main()
{
	int i, lim, c;
	char line[MAXCOLUMN];

	i = 0;
	while ((c = getchar()) != EOF) {
		line[i] = c;

		if ('\t' == c) {
			i = expand(line, i, MAXCOLUMN);
			if (MAXCOLUMN == i) {
				print(line, i);
				i = 0;
			}
		} else if ('\n' == c) {
			print(line, i);
			i = 0;
		} else if (0 == (++i % MAXCOLUMN)) {
			i = fold(line, i);
			print(line, i);
			i = shift(line, i);
		}
	}
	return 0;
}

int fold(char line[], int lim)
{
	int i;

	for (i = lim - 1; i > 0 && ' ' == line[i]; i--)
		;
	if (line[i] != ' ') {
		return i + 1;
	}
	return MAXCOLUMN;
}

void print(char line[], int lim)
{
	int i;

	for(i = 0; i < lim; i++) {
		putchar(line[i]);
	}
	putchar('\n');
}

int shift(char line[], int lim)
{
	int i;

	for (i = 0; i < MAXCOLUMN - lim; i++) {
		line[i] = line[lim + i];
	}
	return MAXCOLUMN - lim;
}

int expand(char line[], int i, int lim)
{
	line[i] = ' ';

	for (i++; (i % TABSTOP) != 0 && i < lim; i++) {
		line[i] = ' ';
	}
	return i;
}
