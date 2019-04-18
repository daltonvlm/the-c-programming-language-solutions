#include <stdlib.h>
#include "kr_syscalls.h"

/* _kr_fillbuf: allocate and fill input buffer */
int _kr_fillbuf(kr_FILE *fp)
{
	int bufsize;

	if ((fp->flag  & (_READ | _EOF | _ERR)) != _READ)
		return kr_EOF;
	bufsize = (fp->flag & _UNBUF) ? 1 : kr_BUFSIZ;
	if (fp->base == kr_NULL)		/* no buffer yet */
		if ((fp->base = (char *) malloc(bufsize)) == kr_NULL)
			return kr_EOF;			/* can't get buffer */
	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->base, bufsize);
	if (--fp->cnt < 0) {
		if (fp->cnt == -1)
			fp->flag |= _EOF;
		else
			fp->flag |= _ERR;
		fp->cnt = 0;
		return kr_EOF;
	}
	return (unsigned char) *fp->ptr++;
}
