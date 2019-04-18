/*
 * malloc accepts a size request without checking its plausibility; free
 * believes that the block it is asked to free contains a valid size field.
 * Improve these routines so they take more pains with error checking.
 */

#include <limits.h>
#include "kr_syscalls.h"

#define MAX_ALLOC SHRT_MAX

/* kr_malloc: general-purpose storage allocator */
void *kr_malloc(unsigned nbytes)
{
	Header *p, *prevp;
	Header *morecore(unsigned);
	unsigned nunits;

	nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
	if (nunits > MAX_ALLOC)
		return NULL;
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

/* ... */

/* kr_free: put block ap in free list */
void kr_free(void *ap)
{
	Header *bp, *p;

	bp = (Header *)ap - 1;	/* point to block header */
	if (bp->s.size <= 0)
		return;
	for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
		if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
			break;	/* freed block at start or end of arena */

	if (bp + bp->s.size == p->s.ptr) {	/* join to upper nbr */
		bp->s.size += p->s.ptr->s.size;
		bp->s.ptr = p->s.ptr->s.ptr;
	} else
		bp->s.ptr = p->s.ptr;
	if (p + p->s.size == bp) {	/* join to lower nbr */
		p->s.size += bp->s.size;
		p->s.ptr = bp->s.ptr;
	} else
		p->s.ptr = bp;
	freep = p;
}
