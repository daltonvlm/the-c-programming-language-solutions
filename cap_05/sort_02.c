#include <stdio.h>
#include <string.h>

#define MAXLINES 	5000	/* max #lines to be sorted */
#define NUMERIC 	1
#define REVERSE		2
#define FOLD		4
#define DIRECTORY	8

#define USAGE "Usage: sort [-dfnr] [+start] [-end]\n"

static char option;
static char *lineptr[MAXLINES];	/* pointers to text lines */
static int start, end;

int readargs(int argc, char *argv[]);
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines, int reverse);

int numcmp(char *s, char *t);
int charcmp(char *s, char *t);

extern void qsort(void *lineptr[], int left, int right, int (*comp)(void *, void *));

/* sort input lines */
main(int argc, char *argv[])
{
	int nlines;			/* number of input lines read */

	if (!readargs(argc, argv))
		return 1;

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		if (option & NUMERIC)
			qsort((void **) lineptr, 0, nlines - 1, (int (*)(void *, void *)) numcmp);
		else
			qsort((void **) lineptr, 0, nlines - 1, (int (*)(void *, void *)) charcmp);
		writelines(lineptr, nlines, option & REVERSE);
		return 0;
	}
	printf("sort: input too big to sort\n");
	return 1;
}

extern int atoi(char *);

int readargs(int argc, char *argv[])
{
	int c;

	while (--argc && ('-' == (c = (*++argv)[0]) || '+' == c)) {
		if ('-' == c && !isdigit(*(argv[0] + 1)))
			while (c = *++argv[0])
				switch (c) {
					case 'd':
						option |= DIRECTORY;
						break;
					case 'f':
						option |= FOLD;
						break;
					case 'n':
						option |= NUMERIC;
						break;
					case 'r':
						option |= REVERSE;
						break;
					default:
						printf("sort: invalid option '%c'\n", c);
						return 0;
				}
		else if ('-' == c)
			end = atoi(argv[0] + 1);
		else
			start = atoi(argv[0] + 1);
	}
	if (start < 0 || start > end) {
		printf("sort: start must be > 0 and <= end\n");
		return 0;
	}
	if (argc) {
		printf(USAGE);
		return 0;
	}
	return 1;
}

#define MAXLEN 1000     /* max length of any input line */

extern int getline(char *, int);
extern char *alloc(int);

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = getline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = alloc(len + 1)) == NULL)
            return -1;
        else {
			if ('\n' == line[len - 1])
				line[len-1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
	}
    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines, int reverse)
{
	int i;

	if (reverse) {
		for (i = nlines - 1; i >= 0; i--)
			printf("%s\n", lineptr[i]);
	} else {
		for (i = 0; i < nlines; i++)
			printf("%s\n", lineptr[i]);
	}
}

#include <ctype.h>

int charcmp(char *s, char *t)
{
	int a, b, i, j, len;
	int fold = option & FOLD;
	int dir = option & DIRECTORY;

	len = strlen(s);
	i = start < len ? start : len;
	len = strlen(t);
	j = start < len ? start : len;

	if (end)
		len = end;
	do {
		if (dir) {
			while (s[i] != '\0' && i < len && !isalnum(s[i]) && s[i] != ' ')
				i++;
			while (t[j] != '\0' && j < len && !isalnum(t[j]) && t[j] != ' ')
				j++;
		}
		a = fold ? tolower(s[i]) : s[i];
		b = fold ? tolower(t[j]) : t[j];
		i++;
		j++;
		if (a == b && '\0' == a)
			return 0;
	} while (a == b);
	return a - b;
}

extern double atof(char *);
char *substr(char *buf, char *s, int start, int end);

int numcmp(char *s, char *t)
{
	double v1, v2;
	char buf[MAXLEN];

	v1 = atof(substr(buf, s, start, end));
	v2 = atof(substr(buf, t, start, end));
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

char *substr(char *buf, char *s, int start, int end)
{
	int i, j, len;

	len = strlen(s);
	if (end && len > end)
		len = end;
	for (i = 0, j = start; j < len; i++, j++)
		buf[i] = s[j];
	buf[i] = '\0';
	return buf;
}
