#define NAME_MAX	14	/* longest filename component; */
								/* system-dependent */

typedef struct {		/* portable directory entry: */
	long ino;					/* inode number */
	char name[NAME_MAX];		/* name + '\0' terminator */
} kr_Dirent;

typedef struct {		/* minimal DIR: no buffering, etc. */
	int fd;					/* file descriptor for directory */
	kr_Dirent d;			/* the directory entry */
} kr_DIR;

kr_DIR *kr_opendir(char *dirname);
kr_Dirent *kr_readdir(kr_DIR *dfd);
void kr_closedir(kr_DIR *dfd);
