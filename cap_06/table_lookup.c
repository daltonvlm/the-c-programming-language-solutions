#include <stdio.h>
#include <stdlib.h>

struct nlist {		/* table entry: */
	struct nlist *next;		/* next entry in chain */
	char *name;				/* defined name */
	char *defn;				/* replacement text */
};

#define HASHSIZE 101

struct nlist *hashtab[HASHSIZE];	/* pointer table */

/* hash: form hash value for strings */
unsigned hash(char *s)
{
	unsigned hashval;

	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}

struct nlist *lookup(char *);
char *strdup(char *);

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
	struct nlist *np;
	unsigned hashval;

	if ((np = lookup(name)) == NULL) {	/* not found */
		np = (struct nlist *) malloc(sizeof(struct nlist));
		if (np == NULL || (np->name = strdup(name)) == NULL)
			return NULL;
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	} else		/* already there */
		free((void *) np->defn);	/* free previous defn */
	if ((np->defn = strdup(defn)) == NULL)
		return NULL;
	return np;
}

/* uninstall: remove (name, defn) from hashtab */
void uninstall(char *name)
{
	extern struct nlist *hashtab[];
	unsigned hashval = hash(name);
	struct nlist **p, *t;

	for (p = &hashtab[hashval]; *p; p = &(*p)->next)
		if (0 == strcmp(name, (*p)->name)) {
			t = (*p)->next;
			free((void *)(*p)->name);
			free((void *)(*p)->defn);
			free(*p);
			*p = t;
			break;
		}
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
	struct nlist *np;

	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return np;	/* found */
	return NULL;		/* not found */
}
