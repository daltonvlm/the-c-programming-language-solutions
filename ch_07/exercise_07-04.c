/*
 * Write a private version of scanf analogous to minprintf from the
 * previous section.
 */

#include <stdio.h>
#include <stdarg.h>

void minscanf(char *fmt, ...)
{
	va_list ap;
	char c, *sval, *p;
	int parse, *ival;
	float *fval;

	va_start(ap, fmt);
	for (p = fmt; *p; p++) {
		while (isspace(*p))
			p++;
		if ('\0' == *p)
			break;
		else if  (*p != '%') {
			while (isspace(c = getchar()))
				;
			if (c != *p)
				break;
			continue;
		}
		switch (*++p) {
			case 'c':
				sval = va_arg(ap, char *);
				*sval = getchar();
				break;
			case 'd':
				ival = va_arg(ap, int *);
				scanf("%d", ival);
				break;
			case 'f':
				fval = va_arg(ap, float *);
				scanf("%f", fval);
				break;
			case 's':
				sval = va_arg(ap, char *);
				while (isspace(c = getchar()))
					;
				if (EOF == c)
					break;
				for (*sval++ = c; !isspace(c = getchar()); sval++)
					*sval = c;
				*sval = '\0';
				if (c != EOF)
					ungetc(c, stdin);
				break;
			default:
				printf("'%c' not supported (maybe, yet)\n", *p);
				break;
		}
	}
}
