/*
 * Write a program to print all input lines that are longer than 80 characters.
 */

#include <stdio.h>

#define MAXLINE 1000
#define MINLINE 80

int getline(char line[], int maxline);

main()
{
    int i;
    char line[MAXLINE];

    while ((i = getline(line, MAXLINE)) > 0) {
        if (i > MINLINE) {
            printf("%s", line);
        }
    }
    puts("");
    return 0;
}

int getline(char s[], int lim)
{
    int i, c;

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
