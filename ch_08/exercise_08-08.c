/*
 * Write a routine bfree(p,n) that will free an arbitrary block p of n
 * characters into the free list maintained by malloc and free. By using
 * bfree, a user can add a static or external array to the free list at any
 * time.
 */

#include "kr_syscalls.h"

unsigned bfree(char *p, unsigned n)
{
	unsigned nunits;
	Header *hdr;

	if (NULL == p || n < sizeof(Header))
		return 0;
	nunits = n / sizeof(Header);
	hdr = (Header *) p;
	hdr->s.size = nunits;
	free(hdr + 1);
	return nunits;
}
