#include <fcntl.h>
#include "kr_syscalls.h"
#define PERMS 0666	/* RW for owner, group, others */

/* kr_fopen: open file, return file ptr */
kr_FILE *kr_fopen(char *name, char *mode)
{
	int fd;
	kr_FILE *fp;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return (kr_FILE *) kr_NULL;
	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if ((fp->flag & (_READ | _WRITE)) == 0)
			break;		/* found free slot */
	if (fp >= _iob + OPEN_MAX)	/* no free slots */
		return (kr_FILE *) kr_NULL;
	if (*mode == 'w')
		fd = creat(name, PERMS);
	else if (*mode == 'a') {
		if ((fd = open(name, O_WRONLY, 0)) == -1)
			fd = creat(name, PERMS);
		lseek(fd, 0L, 2);
	} else
		fd = open(name, O_RDONLY, 0);
	if (fd == -1)			/* couldn't access name */
		return kr_NULL;
	fp->fd = fd;
	fp->cnt = 0;
	fp->base = kr_NULL;
	fp->flag = (*mode == 'r') ? _READ : _WRITE;
	return fp;
}
