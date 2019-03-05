/*
 * Rewrite readlines to store lines in an array supplied by main, rather than
 * calling alloc to maintain storage. How much faster is the program?
 */

#include <stdio.h>
#include <string.h>

#define MAXLINES 5000		/* max #lines to be sorted */
#define BUFSIZE  10000

char *lineptr[MAXLINES];	/* pointers to text lines */

int readlines(char *lineptr[], int nlines, char buf[], int bufsize);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

/* sort input lines */
main()
{
	int nlines;		/* number of input lines read */
    char buf[BUFSIZE];

	if ((nlines = readlines(lineptr, MAXLINES, buf, BUFSIZE)) >= 0) {
		qsort(lineptr, 0, nlines-1);
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("error: input too big to sort\n");
		return 1;
	}
}

#define MAXLEN 1000     /* max length of any input line */
int getline(char *, int);

int bufavailable(char buf[], int bufsize, char *p)
{
    return buf + bufsize - p;
}

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines, char buf[], int bufsize)
{
    int len, nlines;
    char *p, line[MAXLEN];

    p = buf;
    nlines = 0;
    while ((len = getline(line, MAXLEN)) > 0)
        if (nlines >= MAXLINES || (bufavailable(buf, bufsize, p) < len + 1))
            return -1;
        else {
            if ('\n' == line[len-1])    /* delete newline */
                line[len-1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
            p += len+1;
        }
    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right)
{
    int i, last;
    void swap(char *v[], int i, int j);

    if (left >= right)  /* do nothin if array contains */
        return;         /* fewer than two elements */
    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last-1);
    qsort(v, last+1, right);
}
