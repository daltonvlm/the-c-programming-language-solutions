/*
 * In a two's complement number representation, our version of itoa does 
 * not handle the largest negative number, that is, the value of n equal 
 * to -(2 ^ (wordsize-1) ). Explain why not. Modify it to print that value 
 * correctly, regardless of the machine on which it runs.
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

/* itoa: convert n to characters in s */
void itoa(int n, char s[])
{
	int i, sign;

	sign = n;
	i = 0;
	do {		/* generate digits in reverse order */
		s[i++] = abs(n % 10) + '0';		/* get next digit */
	} while ((n /= 10) != 0);			/* delete it */
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}
