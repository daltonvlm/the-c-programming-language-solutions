/*
 * Write the function itob(n, s, b) that converts the integer n into a 
 * base b character representation in the string s. In particular, itob(n, 
 * s, 16) formats n as a hexadecimal integer in s.
 */

#include <stdio.h>
#include <string.h>

#define MAXBASE 10 + 'z' - 'a' + 1

#define abs(n)  ((n) < 0 ? -(n) : (n))

int convert(int c)
{
	return c < 10 ? '0' + c : c - 10 + 'a';
}

/* reverse: reverse string s in place */
void reverse(char s[])
{
	int c, i, j;

	for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
		c = s[i], s[i] = s[j], s[j] = c;
	}
}

void itob(int n, char s[], int b)
{
	int i, sign, digit;

	if (b > MAXBASE) {
		printf("Base %d exceeds the maximum value: %d\n", b, MAXBASE);
		return;
	}

	i = 0;
	sign = n;
	do {
		s[i++] = convert(abs(n % b));
	} while ((n /= b) != 0);

	if (sign < 0) {
		s[i++] = '-';
	}
	s[i] = '\0';
	reverse(s);
}
