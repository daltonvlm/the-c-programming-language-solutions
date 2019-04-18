#include "kr_syscalls.h"

/* kr_malloc: general-purpose storage allocator */
void *kr_malloc(unsigned nbytes)
{
	Header *p, *prevp;
	Header *morecore(unsigned);
	unsigned nunits;

	nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
	if ((prevp = freep) == NULL) {
		base.s.ptr = freep = prevp = &base;
		base.s.size = 0;
	}
	for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
		if (p->s.size >= nunits) {		/* big enough */
			if (p->s.size == nunits)		/* exactly */
				prevp->s.ptr = p->s.ptr;
			else {				/* allocate tail end */
				p->s.size -= nunits;
				p += p->s.size;
				p->s.size = nunits;
			}
			freep = prevp;
			return (void *)(p + 1);
		}
		if (p == freep)		/* wrapped around free list */
			if ((p = morecore(nunits)) == NULL)
				return NULL;	/* none left */
	}
}

#define NALLOC	1024	/* minimum #units to request */

/* morecore: ask system for more memory */
Header *morecore(unsigned nu)
{
	char *cp, *sbrk(int);
	Header *up;

	if (nu < NALLOC)
		nu = NALLOC;
	cp = sbrk(nu * sizeof(Header));
	if (cp == (char *) -1)	/* no space at all */
		return NULL;
	up = (Header *) cp;
	up->s.size = nu;
	kr_free((void *)(up + 1));
	return freep;
}
