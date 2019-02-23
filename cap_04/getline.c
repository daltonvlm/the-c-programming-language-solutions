#include <stdio.h>

int getline(char s[], int lim)
{
	int i, c;

	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
		s[i] = c;
	}
	if ('\n' == c) {
		s[i++] = c;
	}
	s[i] = '\0';
	return i;
}
