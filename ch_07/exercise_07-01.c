/*
 * Write a program that converts upper case to lower or lower case to
 * upper, depending on the name it is invoked with, as found in argv[0].
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

main(int argc, char *argv[])
{
	int c, (*pf)(int);

	pf = tolower;
	if (strstr(argv[0], "upper"))
		pf = toupper;
	while ((c = getchar()) != EOF)
		putchar(pf(c));
	return 0;
}
