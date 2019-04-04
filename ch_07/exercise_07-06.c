/*
 * Write a program to compare two files, printing the first line where they
 * differ.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZE 81

char *progname;

static FILE *openfile(char *fname, char *mode);

main(int argc, char *argv[])
{
	FILE *fp1, *fp2;
	char line1[LINE_SIZE], line2[LINE_SIZE];
	char *p, *q;
	int found = 0;
	
	progname = *argv;
	if (argc < 3) {
		fprintf(stderr, "Usage: %s <file1> <file2>\n", *argv);
		exit(1);
	}
	fp1 = openfile(argv[1], "r");
	fp2 = openfile(argv[2], "r");
	do {
		p = fgets(line1, sizeof(line1), fp1);
		q = fgets(line2, sizeof(line2), fp2);

		if (p && q && strcmp(p, q)) {
			found = 1;
			break;
		}
	} while (p && q);
	if (found || (p != q))
		printf("%s\n", p ? p : q);
	fclose(fp1);
	fclose(fp2);
	return 0;
}

static FILE *openfile(char *fname, char *mode)
{
	FILE *fp = fopen(fname, mode);
	
	if (!fp) {
		fprintf(stderr, "%s: can't open file %s\n", progname, fname);
		exit(1);
	}
	return fp;
}
