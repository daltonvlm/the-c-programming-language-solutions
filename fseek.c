#include "syscalls.h"

/* fseek: sets the file position indicator for the stream pointed to by fp */
int fseek(FILE *fp, long offset, int origin)
{
	int status, cnt;

	status = 0;
	if (fp->flag & _READ) {
		if (1 == origin)
			offset -= fp->cnt;
		fp->cnt = 0;
		status = lseek(fp->fd, offset, origin);
	} else if (fp->flag & _WRITE) {
		cnt = fp->ptr - fp->base;
		fp->cnt = 0;
		if (write(fp->fd, fp->base, cnt) != cnt)
			status = EOF;
		if (status != EOF)
			status = lseek(fp->fd, offset, origin);
	}
	return status != EOF ? 0 : EOF;
}
