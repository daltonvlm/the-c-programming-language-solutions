#include <stdio.h>

#define MAXLINE 80

int getline(char line[], int maxline);

main()
{
	int i;
	char line[MAXLINE];

	while ((i = getline(line, MAXLINE)) > 0) {
		printf("%s", line);
	}
	return 0;
}

int getline(char line[], int lim)
{
	int i, c;

	for (i = 0; (i < lim - 1) * ((c = getchar()) != EOF) * (c != '\n'); i++) {
		line[i] = c;
	}
	if ('\n' == c) {
		line[i] = c;
		i++;
	}
	line[i] = '\0';
	return i;
}
