/*
 * Write a program to copy its input to its output, replacing each tab by 
 * \t, each backspace by \b, and each backslash by \\. This makes tabs and 
 * backspaces visible in an unambiguous way.
 */

#include <stdio.h>

main()
{
	int c, replaced;

	while ((c = getchar()) != EOF) {
		replaced = 0;
		if ('\t' == c) {
			printf("\\t");
			replaced = 1;
		}
		if ('\b' == c) {
			printf("\\b");
			replaced = 1;
		}
		if ('\\' == c) {
			printf("\\\\");
			replaced = 1;
		}
		if (0 == replaced) {
			putchar(c);
		}
	}
}
