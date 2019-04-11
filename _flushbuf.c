#include <stdlib.h>
#include "syscalls.h"

/* _flushbuf: allocate and flush input buffer */
int _flushbuf(int x, FILE *fp)
{
	int cnt, bufsize;

	if ((fp->flag & (_WRITE | _EOF | _ERR)) != _WRITE)
		return EOF;
	bufsize = fp->flag & _UNBUF ? 1 : BUFSIZ;
	if (NULL == fp->base) {
		if (NULL == (fp->base = (char *) malloc(bufsize))) {
			fp->flag |= _ERR;
			return EOF;
		}
	} else {
		cnt = (int) (fp->ptr - fp->base);
		if (write(fp->fd, fp->base, cnt) != cnt) {
			fp->flag |= _ERR;
			return EOF;
		}
	}
	fp->ptr = fp->base;
	*fp->ptr++ = (char) x;
	fp->cnt = bufsize - 1;
	return (unsigned char) x;
}

