#include <stdio.h>

unsigned rightrot(unsigned x, int n)
{
	int i;

	for (i = 0; i < n; i++) {
		x = (x >> 1) | ((x & 1) << ((sizeof(unsigned) * 8 - 1)));
	}
	return x;
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
	unsigned x = 85;

	show_bits(x, sizeof(unsigned));
	while (1) {
		x = rightrot(x, 1);
		show_bits(x, sizeof(unsigned));
		getchar();
	}
	return 0;
}
