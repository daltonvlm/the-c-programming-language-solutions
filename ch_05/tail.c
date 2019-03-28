#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N			10
#define LINESIZE	80
#define MAXLINES	1000

int getline(char *, int);
char *alloc(int);

void shift(char *lines[], int n)
{
	int i;

	for (i = 0; i < n - 1; i++)
		lines[i] = lines[i + 1];
}

int readlines(char *lines[], int maxlines)
{
	int i, n;
	char *p, line[LINESIZE];

	n = i = 0;
	while (i = getline(line, LINESIZE)) {
		if ('\n' == line[i - 1])
			line[i - 1] = '\0';
		if (NULL == (p = alloc(i + 1))) {
			printf("There is no enough space to store more lines.\n");
			return n;
		}
		strcpy(p, line);
		if (n >= maxlines) {
			shift(lines, maxlines);
			n--;
		}
		lines[n++] = p;
	}
	return n;
}

main(int argc, char *argv[])
{
	int i, n;
	char *lines[MAXLINES];

	n = N;
	while (--argc && '-' == (*++argv)[0])
		n = atoi(++argv[0]);

	if (n <= 0 || n > MAXLINES) {
		printf("Number of lines must be > 0 and <= %d.\nDefault of %d lines will be used.\n",
				MAXLINES, N);
		n = N;
	}

	n = readlines(lines, n);
	if (n) {
		printf("The last %d lines are:\n", n);
		for (i = 0; i < n; i++)
			printf("%s\n", lines[i]);
	}
	return 0;
}
