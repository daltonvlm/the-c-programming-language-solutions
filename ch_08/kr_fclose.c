#include <stdlib.h>
#include "kr_syscalls.h"

extern int kr_fflush(kr_FILE *);

/* kr_fclose: close file */
int kr_fclose(kr_FILE *fp)
{
	int status;

	status = kr_fflush(fp);
	status |= close(fp->fd);
	free(fp->base);
	fp->cnt = 0;
	fp->base = NULL;
	fp->flag = 0;
	return status;
}
