/*
 * Write the function strend(s,t), which returns 1 if the string t occurs
 * at the end of the string s, and zero otherwise.
 */

#include <string.h>

int strend(char *s, char *t)
{
    size_t ns = strlen(s);
    size_t nt = strlen(t);

    return ns >= nt ? !strcmp(s + ns - nt, t) : 0;
}
