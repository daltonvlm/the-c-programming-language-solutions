/*
 * The standard library function calloc(n,size) returns a pointer to n
 * objects of size size, with the storage initialized to zero. Write
 * calloc, by calling malloc or by modifying it.
 */

#include "kr_syscalls.h"

void *kr_calloc(unsigned n, unsigned size)
{
	int i, nbytes;
	char *p;

	nbytes = n * size;
	if (NULL == (p = kr_malloc(nbytes)))
		return NULL;
	for (i = 0; i < nbytes; i++)
		p[i] = 0;
	return p;
}
