#include <stdio.h>

unsigned getbits(unsigned x, int p, int n, unsigned y)
{
	x = x & ~(~(~0 << n) << (p + 1 - n));
	y = (y & ~(~0 << n)) << (p + 1 - n);

	return x | y;
}

void show_bits(unsigned x, long size)
{
	int i;

	for (i = (size * 8) - 1; i >= 0; i--) {
		printf("%d", x >> i & 1);
	}
	puts("");
}

main()
{
	int p = 21;
	int n = 10;
	unsigned x = ~0;
	unsigned y = ~0 << n;
	long size = sizeof(int);

	show_bits(x, size);
	show_bits(y, size);
	show_bits(getbits(x, p, n, y), size);
	return 0;
}
