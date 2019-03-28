#include <stdio.h>

#define STOP 		1
#define MAXCOL 		80

main(int argc, char *argv[])
{
    int c, col, nb;
	char cols[MAXCOL + 1];

	init_tabs(argc, argv, cols, MAXCOL);

    nb = 0;
	col = 1;
    while ((c = getchar()) != EOF) {
		if (' ' == c) {
			nb++;
			if (STOP == cols[col]) {
				nb = 0;
				putchar('\t');
			}
		} else if ('\t' == c) {
			for (; cols[col] != STOP; col++)
				if (MAXCOL == col) {
					putchar('\n');
					col = 0;
				}
			putchar('\t');
		} else {
			for (; nb; nb--)
				putchar(' ');
			putchar(c);
		}
		if (MAXCOL == col) {
			for (; nb; nb--)
				putchar(' ');
			putchar('\n');
		}
		col = ('\n' == c || MAXCOL == col) ? 1 : col + 1;
	}
}
