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
