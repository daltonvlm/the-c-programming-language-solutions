#include <stdio.h>

/* getline: read a line into s, return length */
int getline(char s[], int lim)
{
    int c, i;

    for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; i++)
        s[i] = c;
    if ('\n' == c)
        s[i++] = c;
    s[i] = '\0';
    return i;
}

