/*
 * Write a program to print a set of files, starting each new one on a new
 * page, with a title and a running page count for each file.
 */

#include <stdio.h>
#include <stdlib.h>

#define LINE_SIZE 121
#define PAGE_SIZE 20

void printheader(char *fname, int page);

main(int argc, char *argv[])
{
	long lineno, pageno;
	char line[LINE_SIZE], *progname;
	FILE *fp;

	progname = *argv;
	if (1 == argc) {
		fprintf(stderr, "Usage: %s [FILE]...\n", progname);
		return 1;
	}
	while (--argc) {
		if (!(fp = fopen(*++argv, "r"))) {
			fprintf(stderr, "%s: can't open file %s\n", progname,
					*argv);
			continue;
		}
		lineno = pageno = 0;
		while (fgets(line, sizeof(line), fp)) {
			if (0 == lineno % PAGE_SIZE) {
				printheader(*argv, ++pageno);
				lineno = 0;
			}
			printf("%s", line);
			lineno++;
		}
		fclose(fp);
	}
	return 0;
}

void printheader(char *fname, int page)
{
	printf("\f\tFILE: %s\tPage: %d\n\n", fname, page);
}
