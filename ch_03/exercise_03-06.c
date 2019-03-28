/*
 * Write a version of itoa that accepts three arguments instead of two. 
 * The third argument is a minimum field width; the converted number must 
 * be padded with blanks on the left if necessary to make it wide enough.
 */

#include <string.h>

#define abs(n) ((n) < 0 ? -(n) : (n))

/* reverse: reverse string s in place */
void reverse(char s[])
{
	int c, i, j;

	for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
		c = s[i], s[i] = s[j], s[j] = c;
	}
}

void itoa(int n, char s[], int width)
{
	int i, sign;

	sign = n;
	i = 0;
	do {
		s[i++] = abs(n % 10) + '0';
	} while ((n /= 10) != 0);
	if (sign < 0) {
		s[i++] = '-';
	}
	for (; i < width; i++) {
		s[i] = ' ';
	}
	s[i] = '\0';
	reverse(s);
}
