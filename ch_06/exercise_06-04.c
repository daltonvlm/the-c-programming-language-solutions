/*
 * Write a program that prints the distinct words in its input sorted
 * into decreasing order of frequency of occurence. Precede each word
 * by its count.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	MAXWORD	121

char *progname;

struct word {
	char *w;
	int freq;
	struct word *left;
	struct word *right;
};

extern int getword(char *, int);

struct word *addword(struct word *, char *);
struct word *addword_freq(struct word *, struct word *);
void load(struct word **, struct word *);
void wordprint(struct word *);
void wordfree(struct word *);
void errmsg(char *, char *);

main(int argc, char *argv[])
{
	char word[MAXWORD];
	struct word *root, *freq_sorted;

	progname = argv[0];

	root = freq_sorted = NULL;
	while(getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			root = addword(root, word);
	
	load(&freq_sorted, root);
	wordprint(freq_sorted);
	wordfree(root);
	wordfree(freq_sorted);
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
		p->freq = 1;
		p->left = p->right = NULL;
	} else {
		if ((cmp = strcmp(word, p->w)) < 0)
			p->left = addword(p->left, word);
		else if (cmp > 0)
			p->right = addword(p->right, word);
		else
			p->freq++;
	}
	return p;
}

struct word *addword_freq(struct word *dest, struct word *src)
{
	if (!dest) {
		dest = walloc();
		dest->w = strdup(src->w);
		dest->freq = src->freq;
		dest->left = dest->right = NULL;
	} else if (src->freq <= dest->freq)
		dest->left = addword_freq(dest->left, src);
	else
		dest->right = addword_freq(dest->right, src);
	return dest;
}

void load(struct word **storage, struct word *src)
{
	if (src) {
		*storage = addword_freq(*storage, src);
		load(storage, src->left);
		load(storage, src->right);
	}
}

void wordprint(struct word *p)
{
	if (p) {
		wordprint(p->right);
		printf("%d: %s\n", p->freq, p->w);
		wordprint(p->left);
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
