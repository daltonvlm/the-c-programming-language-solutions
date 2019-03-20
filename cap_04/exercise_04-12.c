/*
 * Adapt the ideas of printd to write a recursive version of itoa; that 
 * is, convert an integer into a string by calling a recursive routine.
 */

#define abs(x) ((x) > 0 ? (x) : -(x))

void itoa(int n, char s[])
{
	static int i;

	if (n / 10)
		itoa(n / 10, s);
	else if (n < 0)
		s[i++] = '-';
	s[i++] = abs(n % 10) + '0';
	s[i] = '\0';
}
