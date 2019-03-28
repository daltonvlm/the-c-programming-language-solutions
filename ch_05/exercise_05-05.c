/*
 * Write versions of the library functions strncpy, strncat, and strncmp, 
 * which operate on at most the first n characters of their argument
 * strings. For example, strncpy(s,t,n) copies at most n characters of t
 * to s. Full descriptions are in Appendix B.
 */

#include <stdio.h>

char *my_strncpy(char *s, const char *t, size_t n)
{
    char *p = s;

    while (n-- && (*p++ = *t++))
        ;
    while (n--)
        *p++ = '\0';
    return s;
}

char *my_strncat(char *s, const char *t, size_t n)
{
    char *p = s;

    for (; *p; p++)
        ;
    for (; n-- && (*p = *t); p++, t++)
        ;
    *p = '\0';
    return s;
}

int my_strncmp(const char *s, const char *t, size_t n)
{
    for (; n && *s == *t; s++, t++, n--)
        ;
    return n ? *s - *t : 0;
}

#include <string.h>
main()
{
    int i, n;
    char s[81];

    printf("%d\n", my_strncmp("rio janeiro", "abc", 0));

    return 0;
}
