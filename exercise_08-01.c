/*
 * Rewrite the program cat from Chapter 7 using read, write, open and close
 * instead of their standard library equivalents. Perform experiments to 
 * determine the relative speeds of the two versions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <fcntl.h>

int filecopy(int, int);
void error(char *fmt, ...);

/* cat: concatenate files */
main(int argc, char *argv[])
{
	int fd;
	char *prog = argv[0];	/* program name for errors */

	if (argc == 1) { /* no args; copy standard input */
		if (!filecopy(0, 1))
			error("%s: can't copy stdin to stdout", prog);
	} else
		while (--argc > 0) {
			if ((fd = open(*++argv, O_RDONLY, 0)) == -1)
				error("%s: can't open %s\n", prog, *argv);
			if (!filecopy(fd, 1))
				error("%s: can't copy %s to stdout", prog, *argv);
			close(fd);
		}
	if (ferror(stdout))
		error("%s: error writing stdout\n", prog);
	exit(0);
}

/* filecopy: copy file ifp to file ofp */
int filecopy(int ifd, int ofd)
{
	char buf[BUFSIZ];
	int n;

	while ((n = read(ifd, buf, sizeof buf)) > 0)
		if (write(ofd, buf, n) != n)
			return 0;
	return 1;
}

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
