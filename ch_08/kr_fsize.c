#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kr_syscalls.h"
#include <fcntl.h>			/* flags for read and write */
#include <sys/types.h>		/* typedefs  */
#include <sys/stat.h>		/* structure returned by stat */
#include "kr_dirent.h"

void fsize(char *);

/* print file sizes */
main(int argc, char **argv)
{
	if (argc == 1)		/* default: current directory */
		fsize(".");
	else
		while (--argc)
			fsize(*++argv);
	return 0;
}

void dirwalk(char *, void (*fcn)(char *));

/* fsize: print size of file "name" */
void fsize(char *name)
{
	struct stat stbuf;

	if (stat(name, &stbuf) == -1) {
		fprintf(stderr, "fsize: can't access %s\n", name);
		return;
	}
	if ((stbuf.st_mode & __S_IFMT) == __S_IFDIR)
		dirwalk(name, fsize);
	printf("%8ld %s\n", stbuf.st_size, name);
}

#define MAX_PATH 1024

void dirwalk(char *dir, void (*fcn)(char *))
{
	char name[MAX_PATH];
	kr_Dirent *dp;
	kr_DIR *dfd;

	if ((dfd = kr_opendir(dir)) == kr_NULL) {
		fprintf(stderr, "dirwalk: can't open %s\n", dir);
		return;
	}
	while ((dp = kr_readdir(dfd)) != kr_NULL) {
		if ((strcmp(dp->name, ".") == 0)
		 ||  strcmp(dp->name, "..") == 0)
			continue;	/* skip self and parent */
		if (strlen(dir) + strlen(dp->name) + 2 > sizeof(name))
			fprintf(stderr, "dirwalk: %s/%s too long\n",
				dir, dp->name);
		else {
			sprintf(name, "%s/%s", dir, dp->name);
			(*fcn)(name);
		}
	}
	kr_closedir(dfd);
}

int fstat(int fd, struct stat *);

/* kr_opendir: open a directory for kr_readdir calls */
kr_DIR *kr_opendir(char *dirname)
{
	int fd;
	struct stat stbuf;
	kr_DIR *dp;

	if ((fd = open(dirname, O_RDONLY, 0)) == -1
		|| fstat(fd, &stbuf) == -1
		|| (stbuf.st_mode & __S_IFMT) != __S_IFDIR
		|| (dp = (kr_DIR *) malloc(sizeof(kr_DIR))) == kr_NULL)
		return kr_NULL;
	dp->fd = fd;
	return dp;
}

/* kr_closedir: close directory opened by kr_opendir */
void kr_closedir(kr_DIR *dp)
{
	if (dp) {
		close(dp->fd);
		free(dp);
	}
}

#include <sys/dir.h>	/* local directory structure */

#ifndef DIRSIZ
#define DIRSIZ	14
#endif

/* kr_readdir: read directory entries in sequence */
kr_Dirent *kr_readdir(kr_DIR *dp)
{
	struct direct dirbuf;	/* local directory structure */
	static kr_Dirent d;		/* return: portable structure */

	while (read(dp->fd, (char *) &dirbuf, sizeof(dirbuf))
					== sizeof(dirbuf)) {
		if (dirbuf.d_ino == 0)	/* slot not in use */
			continue;
		d.ino = dirbuf.d_ino;
		strncpy(d.name, dirbuf.d_name, DIRSIZ);
		d.name[DIRSIZ] = '\0';	/* ensure termination */
		return &d;
	}
	return kr_NULL;
}
