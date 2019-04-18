/*
 * Modify the fsize program to print the other information contained in the
 * inode entry.
 */

int stat(char *, struct stat *);
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
	printf("\n%s info:\n", name);
	printf("%-8s %8ld\n", "Size:", stbuf.st_size);
	printf("%-8s %8ld\n", "Ino:", stbuf.st_ino);
	printf("%-8s %8u\n", "UID:", stbuf.st_uid);
	printf("%-8s %8u\n", "GID:", stbuf.st_gid);
}
