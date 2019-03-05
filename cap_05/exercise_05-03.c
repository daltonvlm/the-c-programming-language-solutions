/*
 * Write a pointer version of the function strcat that we showed in Chapter 2: strcat(s,t)
 * that copies the string t to the end of s.
 */

void strcat(char *s, char *t)
{
	for (; *s; s++);
	while (*s++ = *t++);
}
