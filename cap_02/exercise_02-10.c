#include <stdio.h>

/* lower: convert c to lower case; ASCII only */
int lower(int c)
{
	return (c >= 'A' && c <= 'Z' ) ? c + 'a' - 'A' : c;
}

main()
{
	int c;

	for (c = 'A'; c <= 'Z'; c++) {
		printf("%c%c", tolower(c), 'Z' == c ? '\n' : ' ');
	}
	return 0;
}
