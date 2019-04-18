#include "kr_syscalls.h"

/* kr_fseek: sets the file position indicator for the stream pointed to by fp */
int kr_fseek(kr_FILE *fp, long offset, int origin)
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
			status = kr_EOF;
		if (status != kr_EOF)
			status = lseek(fp->fd, offset, origin);
	}
	return status != kr_EOF ? 0 : kr_EOF;
}
