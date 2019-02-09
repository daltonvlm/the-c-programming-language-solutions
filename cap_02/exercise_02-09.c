#include <stdio.h>

/* bitcount: count 1 bits in x */
int bitcount(unsigned x)
{
	int b;

	for (b = 0; x != 0; x &= x - 1) {
		b++;
	}
	return b;
}

main()
{
	unsigned x;

	for (x = ~0; x != 0; x >>= 1) {
		printf("%d\n", bitcount(x));
	}
	return 0;
}
