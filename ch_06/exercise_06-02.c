/*
 * Write a program that reads a C program and prints in alphabetical order
 * each group of varable names that are indentical in the first 6 
 * characters, but different somewhere thereafter. Don't count words within
 * strings and comments. Make 6 a parameter that can be set from the 
 * command line.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NCHAR	6
#define MAXWORD	100

struct word {
	char *w;
	struct word *left;
	struct word *right;
};

struct tnode {
	struct word *w;
	struct tnode *left;
	struct tnode *right;
};

char *progname;

struct tnode *addtree(struct tnode *, char *, int);
void treeprint(struct tnode *);
void treefree(struct tnode *);
void errmsg(char *progname, char *msg);
extern int getword(char *, int);

main(int argc, char *argv[])
{
	int nchar;
	char word[MAXWORD];
	struct tnode *root;

	progname = argv[0];
	nchar = NCHAR;

	/* parse command line argument */
	while (--argc && '-' == *(++argv)[0])
		switch (*++argv[0]) {
			case 'n':
				if (isdigit(*++argv[0]))
					nchar = atoi(argv[0]);
				else if ('\0' == *argv[0])
					errmsg(progname, "option '-n' requires an argument");
				else
					errmsg(progname, "invalid number for '-n'");
				break;
			default:
				errmsg(progname, "invalid option");
				break;
		}

	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			root = addtree(root, word, nchar);
	treeprint(root);
	treefree(root);
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

struct word *addword(struct word *p, char *word)
{
	int cmp;

	if (!p) {
		p = walloc();
		p->w = strdup(word);
		p->left = p->right = NULL;
	} else {
		if ((cmp = strcmp(word, p->w)) < 0)
			p->left = addword(p->left, word);
		else if (cmp > 0)
			p->right = addword(p->right, word);
	}
	return p;
}

struct tnode *talloc(void)
{
	return (struct tnode *) alloc(sizeof(struct tnode));
}

struct tnode *addtree(struct tnode *p, char *word, int nchar)
{
	int dif;

	if (!p) {
		p = talloc();
		p->w = addword(NULL, word);
		p->left = p->right = NULL;
	} else {
		if ((dif = strncmp(word, p->w->w, nchar)) < 0)
			p->left = addtree(p->left, word, nchar);
		else if (dif > 0)
			p->right = addtree(p->right, word, nchar);
		else 
			p->w = addword(p->w, word);
	}
	return p;
}

void wordprint(struct word *p)
{
	if (p) {
		wordprint(p->left);
		printf("%s ", p->w);
		wordprint(p->right);
	}
}

void treeprint(struct tnode *p)
{
	if (p) {
		treeprint(p->left);
		wordprint(p->w);
		puts("");
		treeprint(p->right);
	}
}

void wordfree(struct word *p)
{
	if (p) {
		wordfree(p->left);
		wordfree(p->right);
		free(p->w);
		free(p);
	}
}

void treefree(struct tnode *p)
{
	if (p) {
		treefree(p->left);
		treefree(p->right);
		wordfree(p->w);
		free(p);
	}
}
