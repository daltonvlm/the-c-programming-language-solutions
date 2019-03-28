#include <stdlib.h>
#include <stdio.h>

#define TABSTOP 8

void init_tabs(int argc, char *argv[], char *cols, int ncols)
{
	int i, c, d, ts, setdefault = 1;
	int m, n;

	m = n = 0;
	while (--argc && ('-' == (c = (*++argv)[0]) || '+' == c)) {
		switch (*++argv[0]) {
			case 'm':
				if ('-' == c) {
					setdefault = 0;
					m = atoi(++argv[0]);
				}
				break;
			case 'n':
				if ('+' == c) {
					setdefault = 0;
					n = atoi(++argv[0]);
				}
				break;
		}
	}
	for (i = 1; i <= ncols; i++)
		cols[i] = 0;
	if (n)
		for (i = m; i <= ncols; i += n)
			cols[i] = 1;
	while (argc--)
		if ((ts = atoi(*argv++)) && ts <= ncols) {
			setdefault = 0;
			cols[ts] = 1;
		}
	if (setdefault)
		for (i = TABSTOP; i <= ncols; i += TABSTOP)
			cols[i] = 1;
}

