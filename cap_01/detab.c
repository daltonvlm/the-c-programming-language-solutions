#include <stdio.h>

#define TABSTOP 8

main()
{
	int col, c, nb;

	for (col = 1; (c = getchar()) != EOF; col++) {
		if ('\t' == c) {
			nb = TABSTOP - (col % TABSTOP) + 1;
			col += nb - 1;
			while (nb--)
				putchar(' ');
		} else {
			if ('\n' == c)
				col = 0;
			putchar(c);
		}
	}
	return 0;
}
