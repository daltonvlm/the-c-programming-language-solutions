/*
 * Write a recursive version of the function reverse(s), which reverses
 * the string s in place.
 */

#include <string.h>

void reverse(char s[])
{
	static int i;
	char c;
	int last = strlen(s) - 1;

	if (s[i] != '\0') {
		c = s[i];
		s[i] = s[last - i];
		s[last - i] = c;
		i++;
		reverse(s);
	}
}
