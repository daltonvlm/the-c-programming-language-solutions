#include <stdio.h>

unsigned invert(unsigned x, int p, int n)
{
	return x ^ ~(~0 << n) << (p + 1 -n);
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
	int p = 4;
	int n = 3;
	unsigned x = 85;
	long size = sizeof(char);

	show_bits(x, size);
	show_bits(invert(x, p, n), size);
	return 0;
}
