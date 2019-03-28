/*
 * Write a cross-referencer that prints a list of all words in a document,
 * and, for each word, a list of the line numbers on which it occurs.
 * Remove noise words like "the", "and", and so on.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	MAXLINE	121

const char *noises[] = {
	"a",
	"an",
	"and",
	"of",
	"that",
	"the",
	"these",
	"this",
	"those",
	NULL
};

char *progname;

struct line {
	int lineno;
	struct line *left;
	struct line *right;
};

struct word {
	char *w;
	struct line *ln;
	struct word *left;
	struct word *right;
};

extern void ungetch(int);
extern int getch(void);
extern int getline(char *, int);
extern int getword(char *, int);

struct word *addword(struct word *, char *, int);
void wordprint(struct word *);
void wordfree(struct word *);
void errmsg(char *, char *);

main(int argc, char *argv[])
{
	int actualln, n;
	char line[MAXLINE];
	struct word *root;

	progname = argv[0];

	actualln = 0;
	root = NULL;
	while (n = getline(line, MAXLINE)) {
		if ('\n' == line[n - 1])
			actualln++;
		ungetch(EOF);
		while (n--)
			ungetch(line[n]);
		while(getword(line, MAXLINE) != EOF)
			if (isalpha(line[0]))
				root = addword(root, line, actualln);
	}
	wordprint(root);
	wordfree(root);
	return 0;
}

void errmsg(char *progname, char *msg)
{
	printf("%s: %s\n", progname, msg);
	exit(1);
}

void *alloc(size_t n)
{
	void *p = malloc(n);

	if (!p)
		errmsg(progname, "can't alloc memory");
	return p;
}

struct line *lalloc(void)
{
	return (struct line *) alloc(sizeof(struct line));
}

struct line *addline(struct line *p, int lineno)
{
	if (!p) {
		p = lalloc();
		p->lineno = lineno;
		p->left = NULL;
		p->right = NULL;
	} else if (lineno < p->lineno)
		p->left = addline(p->left, lineno);
	else if (lineno > p->lineno)
		p->right = addline(p->right, lineno);
	return p;
}

char *strdup(char *word)
{
	char *p = (char *) alloc(strlen(word) + 1);
	
	strcpy(p, word);
	return p;
}

struct word *walloc(void)
{
	return (struct word *) alloc(sizeof(struct word));
}

int isnoise(char *word)
{
	char **p;

	for (p = (char **)noises; *p; p++)
		if (0 == strcmp(word, *p))
			return 1;
	return 0;
}

struct word *addword(struct word *p, char *word, int lineno)
{
	int cmp;

	if (!isnoise(word))
		if (!p) {
			p = walloc();
			p->w = strdup(word);
			p->ln = addline(NULL, lineno);
			p->left = p->right = NULL;
		} else {
			if ((cmp = strcmp(word, p->w)) < 0)
				p->left = addword(p->left, word, lineno);
			else if (cmp > 0)
				p->right = addword(p->right, word, lineno);
			else
				p->ln = addline(p->ln, lineno);
		}
	return p;
}

void lineprint(struct line *p)
{
	if (p) {
		lineprint(p->left);
		printf("%d ", p->lineno);
		lineprint(p->right);
	}
}

void wordprint(struct word *p)
{
	if (p) {
		wordprint(p->left);
		printf("%-10s ", p->w);
		lineprint(p->ln);
		puts("");
		wordprint(p->right);
	}
}

void linefree(struct line *p)
{
	if (p) {
		linefree(p->left);
		linefree(p->right);
		free(p);
	}
}

void wordfree(struct word *p)
{
	if (p) {
		wordfree(p->left);
		wordfree(p->right);
		free(p->w);
		linefree(p->ln);
		free(p);
	}
}
