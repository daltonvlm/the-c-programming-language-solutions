/*
 * Write versions of the library functions strncpy, strncat, and strncmp, which operate on
 * at most the first n characters of t to s. Full descriptions are a Appendix B.
 */

char *my_strncpy(char *s, const char *t, size_t n)
{
	size_t i;
	char *p;

	for (i=0, p=s; i<n && (*p++ = *t++); i++)
		;
	for (; i < n; i++)
		*p++ = '\0';
	return s;
}

char *my_strncat(char *s, const char *t, size_t n)
{
	size_t i;
	char *p;

	for (p = s; *p; p++)
		;
	for (i = 0; i < n && (*p++ = *t++); i++)
		;
	*p = '\0';
	return s;
}

int my_strncmp(const char *s, const char *t, size_t n)
{
	size_t i;

	for (i=0; i<n && *s && *s == *t; s++, t++, i++)
		;
	if (i < n)
		return *s - *t;
	return 0;
}
