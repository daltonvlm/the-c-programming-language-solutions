#include <stdlib.h>
#include "syscalls.h"

extern int fflush(FILE *);

/* fclose: close file */
int fclose(FILE *fp)
{
	int status;

	status = fflush(fp);
	status |= close(fp->fd);
	free(fp->base);
	fp->cnt = 0;
	fp->base = NULL;
	fp->flag = 0;
	return status;
}
