/*
 * Rewrite fopen and _fillbuf with fields instead of explicit bit
 * operations. Compare code size and execution speed.
 */

#include <fcntl.h>
#include "syscalls.h"
#define PERMS 0666	/* RW for owner, group, others */

/* fopen: open file, return file ptr */
FILE *fopen(char *name, char *mode)
{
	int fd;
	FILE *fp;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;
	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if (fp->flag.read == 0 && fp->flag.write == 0)
			break;		/* found free slot */
	if (fp >= _iob + OPEN_MAX)	/* no free slots */
		return NULL;
	if (*mode == 'w')
		fd = creat(name, PERMS);
	else if (*mode == 'a') {
		if ((fd = open(name, O_WRONLY, 0)) == -1)
			fd = creat(name, PERMS);
		lseek(fd, 0L, 2);
	} else
		fd = open(name, O_RDONLY, 0);
	if (fd == -1)			/* couldn't access name */
		return NULL;
	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;
	fp->read = fp->write = fp->unbuf = fp->eof = fp->err = 0;
	if (*mode == 'r')
		fp->flag.read = 1;
	else
		fp->flag.write = 1;
	return fp;
}

#include <stdlib.h>

/* _fillbuf: allocate and fill input buffer */
int _fillbuf(FILE *fp)
{
	int bufsize;

	if (!fp->flag.read || fp->flag.eof || fp->flag.err)
		return EOF;
	bufsize = fp->flag.unbuf ? 1 : BUFSIZ;
	if (fp->base == NULL)		/* no buffer yet */
		if ((fp->base = (char *) malloc(bufsize)) == NULL)
			return EOF;			/* can't get buffer */
	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->base, bufsize);
	if (--fp->cnt < 0) {
		if (fp->cnt == -1)
			fp->flag.eof = 1;
		else
			fp->flag.err = 1;
		fp->cnt = 0;
		return EOF;
	}
	return (unsigned char) *fp->ptr++;
}
