/*
 * Write a function righrot(x, n) that returns the value of the integer x rotated
 * to the right by n bit positions.
 */

unsigned rightrot(unsigned x, int n)
{
	int i;

	for (i = 0; i < n; i++) {
		x = (x >> 1) | ((x & 1) << ((sizeof(unsigned) * 8 - 1)));
	}
	return x;
}
