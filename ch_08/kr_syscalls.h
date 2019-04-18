#include <unistd.h>

#define kr_NULL		0
#define kr_EOF		(-1)
#define kr_BUFSIZ	1024

#define OPEN_MAX	20 /* max #files open at once */

typedef struct _iobuf {
	int cnt;		/* characters left */
	char *ptr;		/* next character position */
	char *base;		/* location of buffer */
	int flag;		/* mode of file access */
	int fd;			/* file descriptor */
} kr_FILE;
extern kr_FILE _iob[OPEN_MAX];

#define kr_stdin	(&_iob[0])
#define	kr_stdout	(&_iob[1])
#define kr_stderr	(&_iob[2])

enum flags {
	_READ 	= 01,		/* file open for reading */
	_WRITE 	= 02,		/* file open for writing */
	_UNBUF 	= 04,		/* file is unbuffered */
	_EOF	= 010,		/* EOF has occured on this file */
	_ERR	= 020		/* error ocurred on this file */
};

int _kr_fillbuf(kr_FILE *);
int _kr_flushbuf(int, kr_FILE *);

kr_FILE *kr_fopen(char *, char *);
int kr_fclose(kr_FILE *);
int kr_fflush(kr_FILE *);
int kr_fseek(kr_FILE *, long, int);

#define kr_feof(p)		(((p)->flag & _EOF) != 0)
#define kr_ferror(p)	(((p)->flag & _ERR) != 0)
#define kr_fileno(p)	((p)->fd)

#define kr_getc(p)		(--(p)->cnt >= 0 \
							? (unsigned char) *(p)->ptr++ : _kr_fillbuf(p))
#define kr_putc(x,p)	(--(p)->cnt >= 0 \
							? *(p)->ptr++ = (x) : _kr_flushbuf((x), p));

#define kr_getchar()	kr_getc(kr_stdin)
#define kr_putchar(x)	kr_putc((x), kr_stdout)

typedef long Align;	/* for alignment to long boundary */

union header {		/* block header: */
	struct {
		union header *ptr;	/* next block if on free list */
		unsigned size;		/* size of this block */
	} s;
	Align x;		/* force alignment of blocks */
};

typedef union header Header;

Header base;			/* empty list to get started */
Header *freep;	/* start of free list */

void *kr_malloc(unsigned);
void kr_free(void *);
