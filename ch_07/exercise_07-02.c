/*
 * Write a program that will print arbitrary input in a sensible way. As a
 * minimum, it should print non-graphic characters in octal or hexadecimal
 * according to local custom, and break long text lines.
 */

#include <stdio.h>
#include <ctype.h>

#define LINEWIDTH 60

enum option { OCT, HEX };
char *progname;

main(int argc, char *argv[])
{
	int c, opt = OCT;
	long n = 0;
	char fmt[81];

	progname = argv[0];
	while (--argc && ('-' == *(++argv)[0]))
		while (c = *++argv[0])
			switch (c) {
				case 'o':
					opt = OCT;
					break;
				case 'x':
				case 'X':
					opt = HEX;
					sprintf(fmt, "%%%c", c);
					break;
				default:
					printf("%s: invalid option: '%c'\n", progname, c);
					return 1;
					break;
			}
	if (argc) {
		printf("Usage: %s [-oh]\n", progname);
		return 1;
	}
	while ((c = getchar()) != EOF) {
		n++;
		if (!isgraph(c))
			printf(OCT == opt ? "%o" : fmt, c);
		else
			printf("%c", c);
		if (0 == (n % LINEWIDTH))
			putchar('\n');
	}
	puts("");
	return 0;
}
