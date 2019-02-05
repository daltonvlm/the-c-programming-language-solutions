#include <stdio.h>

#define IN 	1
#define OUT	0
#define MAX_LENGTH 21

/* This is not a perfect solution */
main()
{
	int c, i, length, state, max_bars;
	int histogram[MAX_LENGTH];

	for (i = 0; i < MAX_LENGTH; i++) {
		histogram[i] = 0;
	}

	length = max_bars = 0;
	state = OUT;

	while ((c = getchar()) != EOF) {
		if (' ' == c || '\t' == c || '\f' == c || '\v' == c || '\n' == c) {
			if (IN == state) {
				histogram[length]++;
				if (histogram[length] > max_bars) {
					max_bars = histogram[length];
				}
				length = 0;
			}
			state = OUT;
		} else {
			state = IN;
			length++;
		}
	}

	/* horizontal bars */
	printf("  ");
	for (i = 1; i <= max_bars; i++) {
		printf(" %2d", i);
	}
	puts("");
	for (i = 1; i < MAX_LENGTH; i++) {
		int j;
		printf("%2d", i);
		for (j = 0; j < histogram[i]; j++) {
			printf("  |");
		}
		puts("");
	}

	puts("");

	/* vertical bars */
	for (i = max_bars; i > 0; i--) {
		int j;

		printf("%2d ", i);
		for (j = 1; j < MAX_LENGTH; j++) {
			if (histogram[j] == i) {
				printf(" __");
				histogram[j]--;
			} else {
				printf("   ");
			}
		}
		puts("");
	}
	printf("   ");
	for (i = 1; i < MAX_LENGTH; i++) {
		printf(" %2d", i);
	}
	puts("");
}
