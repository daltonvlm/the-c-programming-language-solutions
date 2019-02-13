/*
 * Write a function reverse(s) that reverses the character string s. Use it to
 * write a program that reverses its input a line at a time.
 */

#include <stdio.h>

#define MAXLINE 81

void reverse(char line[]);
int getline(char line[], int maxline);

main()
{
    char line[MAXLINE];

    while (getline(line, MAXLINE) > 0) {
        reverse(line);
        printf("%s", line);
    }
    return 0;
}

void reverse(char s[])
{
    int i, j;

    for (i=0, j=0; s[j] != '\0'; j++)
        ;
    for (j--; i < j; i++, j--) {
        char tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
    }
}

int getline(char s[], int lim)
{
    int c, i;

    for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; i++) {
        s[i] = c;
    }
    if ('\n' == c) {
        s[i] = c;
        i++;
    }
    s[i] = '\0';
    return i;
}
