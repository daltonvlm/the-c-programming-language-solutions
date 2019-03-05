/*
 * Write the function strend(s,t), which returns 1 if the string t occurs
 * at the end of the string s, and zero otherwise.
 */

int strend(char *s, char *t)
{
	char *p, *q;

	for (p = s; *p; p++)
		;
	for (q = t; *q; q++)
		;
	while (p > s && q > t && *--p == *--q)
		;
	return *p == *q;
}
