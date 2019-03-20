#include <stdio.h>

#define STOP 		1
#define MAXCOL 		80

main(int argc, char *argv[])
{
	int col, c;
	char cols[MAXCOL + 1];

	init_tabs(argc, argv, cols, MAXCOL);

	col = 1;
	while ((c = getchar()) != EOF) {
		if ('\t' == c) {
			while (cols[col] != STOP) {
				putchar(' ');
				col++;
				if (col > MAXCOL) {
					putchar('\n');
					col = 1;
				}
			}
			putchar(' ');
		} else
			putchar(c);
		col = ('\n' == c || col >= MAXCOL) ? 1 : col + 1;
	}
	return 0;
}
