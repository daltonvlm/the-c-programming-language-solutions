/*
 * Write a program to count blanks, tabs, and newlines.
 */

#include <stdio.h>

main()
{
	int c, nb, nt, nl;

	nb = nt = nl = 0;
	while ((c = getchar()) != EOF) {
		if (' ' == c) {
			++nb;
		}
		if ('\t' == c) {
			++nt;
		}
		if ('\n' == c) {
			++nl;
		}
	}
	printf("blanks = %d, tabs = %d, newlines = %d\n",
			nb, nt, nl);
}
