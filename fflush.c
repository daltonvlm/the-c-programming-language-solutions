#include "syscalls.h"

static int _fflush(FILE *);

/* 
 * fflush: forces a write for output streams or discard buffered data for
 * input streams.
 */
int fflush(FILE *fp)
{
	int status = 0;

	if (NULL == fp) {	/* flushes all open output streams */
		for (fp = _iob + 1; fp - _iob < OPEN_MAX; fp++)
			if (fp->flag & _WRITE)
				status |= _fflush(fp);
	} else
		status = _fflush(fp);
	return status;
}

static int _fflush(FILE *fp)
{
	int status = 0;

	if (fp->flag & _WRITE)
		status = _flushbuf(NULL, fp);
	fp->cnt = fp->flag & _UNBUF ? 1 : BUFSIZ;
	fp->ptr = fp->base;
	return status;
}
