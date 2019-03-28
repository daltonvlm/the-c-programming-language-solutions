/*
 * Write a program to copy its input to its output, replacing each string 
 * of one or more blanks by a single blank.
 */

#include <stdio.h>

main()
{
    int c, inspace;

    inspace = 0;
    while ((c = getchar()) != EOF) {
        if (' ' == c) {
            if (0 == inspace) {
                inspace = 1;
            }
        }
        if (c != ' ') {
            if (1 == inspace) {
                inspace = 0;
                putchar(' ');
            }
            putchar(c);
        }
    }
}
