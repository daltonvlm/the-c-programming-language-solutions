/*
 * Write a pointer version of the function strcat that we showed in 
 * Chapter 2: strcat(s,t) that copies the string t to the end of s.
 */

/* strcat: concatenate t to end of s; s must be big enough */
void strcat(char *s, char *t)
{
    while (*s)
        s++;
    while (*s++ = *t++)   /* copy t */
        ;
}
