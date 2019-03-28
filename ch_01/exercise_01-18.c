/*
 * Write a program to remove trainling blanks and tabs from each line of 
 * input, and to delete entirely blank lines.
 */

#include <stdio.h>

#define MAXLINE 1000

int getline(char line[], int maxline);
int isblank(int c);

main()
{
    int i;
    char line[MAXLINE];

    while ((i = getline(line, MAXLINE)) > 0) {
        printf("%s", line);
    }
    return 0;
}

int getline(char s[], int lim)
{
    int i, j, c, search, found_non_blank;

    search = 1;
    found_non_blank = 0;
    i = 0;
    while (search) {
        for (j=i; j<lim-1 && isblank(c=getchar()); j++) {
            s[j] = c;
        }
        if ((EOF == c)) {
            s[i] = '\0';
            search = 0;
        } else if (lim-1 == j) {
            if (found_non_blank) {
                s[i] = '\0';
                search = 0;
            }
        } else if (c != '\n') {
            found_non_blank = 1;
            s[j] = c;
            i = j+1;
        } else if (found_non_blank) {
            s[i++] = c;
            s[i] = '\0';
            search = 0;
        }
    }
    return i;
}

int isblank(int c)
{
    return ' ' == c || '\t' == c || '\f' == c || '\v' == c;
}
