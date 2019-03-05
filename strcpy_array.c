/* strcpy: copy t to s; array subscript version */
void strcpy(char *s, char *t)
{
    int i;

    i = 0;
    while ((s[i] = t[i]) != '\0')
        i++;
}

#include <stdio.h>
main()
{
    char s[81];

    strcpy(s, "rio de janeiro");
    printf("%s\n", s);
    return 0;
}
