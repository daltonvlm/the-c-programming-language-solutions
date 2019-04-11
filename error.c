#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

/* error: print an error message an die */
void error(char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	fprintf(stderr, "error: ");
	vfprintf(stderr, fmt, args);
	fprintf(stderr, "\n");
	va_end(args);
	exit(1);
}
