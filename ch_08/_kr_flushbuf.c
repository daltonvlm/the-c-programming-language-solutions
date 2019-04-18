#include <stdlib.h>
#include "kr_syscalls.h"

/* _kr_flushbuf: allocate and flush input buffer */
int _kr_flushbuf(int x, kr_FILE *fp)
{
	int cnt, bufsize;

	if ((fp->flag & (_WRITE | _EOF | _ERR)) != _WRITE)
		return kr_EOF;
	bufsize = fp->flag & _UNBUF ? 1 : kr_BUFSIZ;
	if (kr_NULL == fp->base) {
		if (kr_NULL == (fp->base = (char *) malloc(bufsize))) {
			fp->flag |= _ERR;
			return kr_EOF;
		}
	} else {
		cnt = (int) (fp->ptr - fp->base);
		if (write(fp->fd, fp->base, cnt) != cnt) {
			fp->flag |= _ERR;
			return kr_EOF;
		}
	}
	fp->ptr = fp->base;
	*fp->ptr++ = (char) x;
	fp->cnt = bufsize - 1;
	return (unsigned char) x;
}

