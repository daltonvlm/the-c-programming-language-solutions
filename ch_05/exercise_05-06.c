/* Rewrite appropriate programs from earlier chapters and exercises with
 * pointers instead of array indexing. Good possibilities include getline
 * (Chapters 1 and 4), atoi, itoa, and their variants (Chapters 2, 3, and
 * 4), reverse (Chapter 3), and strindex and getop (Chapter 4).
 */

#include <stdio.h>

/* getline: get line into s, return length */
int getline(char *s, int lim)
{
    int c = '\0';
    char *p = s;

    while (--lim > 0 && (c=getchar())!=EOF && c!='\n')
        *p++ = c;
    if (c == '\n')
        *p++ = c;
    *p = '\0';
    return p - s;
}

/* atoi: convert s to integer */
int atoi(char *s)
{
    int n;

    n = 0;
    while (*s >= '0' && *s <= '9')
        n = 10 * n + (*s++ - '0');
    return n;
}

/* itoa: convert n to characters in s */
void itoa(int n, char *s)
{
    int sign;
    char *p = s;
    void reverse(char *);

    if ((sign = n) < 0) /* record sign */
        n = -n;         /* make n positive */
    do {        /* generate digits in reverse order */
        *p++ = n % 10 + '0';      /* get next digit */
    } while ((n /= 10) > 0);        /* delete it */
    if (sign < 0)
        *p++ = '-';
    *p = '\0';
    reverse(s);
}

#include <ctype.h>

/* atof: convert string s to double */
double atof(char *s)
{
    double val, power;
    int sign;

    for (; isspace(*s); s++)     /* skip whitespace */
        ;
    sign = (*s == '-') ? -1 : 1;
    if (*s == '+' || *s == '-')
        s++;
    for (val = 0.0; isdigit(*s); s++)
        val = 10 * val + (*s - '0');
    if (*s == '.')
        s++;
    for (power = 1.0; isdigit(*s); s++) {
        val = 10 * val + (*s - '0');
        power *= 10;
    }
    return sign * val / power;
}

#include <string.h>

/* reverse: reverse string s in place */
void reverse(char *s)
{
    char c;
    char *t = s + strlen(s) - 1;

    for (; s < t; s++, t--) {
        c = *s;
        *s = *t;
        *t = c;
    }
}

int strindex(char *src, char *search)
{
    char *orig, *p, *q;

	for (orig = src; *src; src++) {
		for (p=search, q=src; *p && *p == *q; p++, q++)
			;
		if (p!=search && !*p)
            return src - orig;
	}
	return -1;
}

#define NUMBER '0'

/* getop: get next operator or numeric operand */
int getop(char *s)
{
    int c;
    int getch(void);
    void ungetch(int);

    while ((*s = c = getch()) == ' ' ||  c == '\t')
        ;
    *(s+1) = '\0';
    if (!isdigit(c) && c != '.')
        return c;       /* not a number */
    if (isdigit(c))     /* collect integer part */
        while (isdigit(*++s = c = getch()))
            ;
    if (c == '.')       /* collect fraction part */
        while (isdigit(*++s = c = getch()))
            ;
    *s = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}
