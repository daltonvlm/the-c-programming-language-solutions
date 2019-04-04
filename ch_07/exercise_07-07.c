/*
 * Modify the pattern finding program of Chapter 5 to take its input from
 * a set of named files or, if no files are named as arguments, from the
 * standard input. Should the file name be printed when a matching line is
 * found?
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZE 		121
#define ERROR_MSG_SIZE 	81

void errormsg(char *);
FILE *openfile(char *, char *);
void readinput(char *, int, char *, FILE *, int, int);

char *progname;
char emsg[ERROR_MSG_SIZE];

/* find: print lines that match pattern from 1st arg */
main(int argc, char *argv[])
{
	char line[LINE_SIZE];
	char *pattern;
    int c, except, number;
	FILE *fp;

	progname = *argv;
	except = number = 0;
    while (--argc && (*++argv)[0] == '-')
        while (c = *++argv[0])
            switch (c) {
                case 'x':
                    except = 1;
                    break;
                case 'n':
                    number = 1;
                    break;
                default:
					sprintf(emsg, "illegal option '%c'", c);
					errormsg(emsg);
					break;
            }
    if (!argc) {
		sprintf(emsg, "missing pattern");
		errormsg(emsg);
	}
	argc--;
	pattern = *argv++;
	if (!argc)
		readinput(line, LINE_SIZE, pattern, stdin, number, except);
	else
		while (argc--) {
			fp = openfile(*argv, "r");
			printf("\n%s:\n", *argv);
			readinput(line, LINE_SIZE, pattern, fp, number, except);
			fclose(fp);
			argv++;
		}
    return 0;
}

void errormsg(char *emsg)
{
	fprintf(stderr,"%s: %s\n", progname, emsg);
	exit(1);
}

FILE *openfile(char *fname, char *mode)
{
	FILE *fp = fopen(fname, mode);
	if (!fp) {
		sprintf(emsg, "can't open file %s", fname);
		errormsg(emsg);
	}
	return fp;
}

void readinput(char *line, int len, char *pattern, FILE *stream,
		int number, int except)
{
	long lineno = 0;

	while (fgets(line, len, stream)) {
		lineno++;
		if ((strstr(line, pattern) != NULL) != except) {
			if (number)
				printf("%ld: ", lineno);
			printf("%s", line);
		}
	}
}
