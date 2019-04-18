#include "kr_syscalls.h"

static int _fflush(kr_FILE *);

/* 
 * kr_fflush: forces a write for output streams or discard buffered data for
 * input streams.
 */
int kr_fflush(kr_FILE *fp)
{
	int status = 0;

	/* flushes all open output streams */
	if (kr_NULL == fp) {
		for (fp = _iob + 1; fp - _iob < OPEN_MAX; fp++)
			if (fp->flag & _WRITE)
				status |= _fflush(fp);
	} else
		status = _fflush(fp);
	return status;
}

static int _fflush(kr_FILE *fp)
{
	int status = 0;

	if (fp->flag & _WRITE)
		status = _kr_flushbuf(kr_NULL, fp);
	fp->cnt = fp->flag & _UNBUF ? 1 : kr_BUFSIZ;
	fp->ptr = fp->base;
	return status;
}
