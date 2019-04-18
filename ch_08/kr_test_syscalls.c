#include "kr_syscalls.h"

kr_FILE _iob[OPEN_MAX] = {		/* stdin, stdout, stderr: */
	{ 0, (char *) 0, (char *) 0, _READ, 0 },
	{ 0, (char *) 0, (char *) 0, _WRITE, 1 },
	{ 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2 }
};

int main(int argc, char *argv[])
{
	char *msg = "testing syscalls";
	kr_FILE *fp = kr_fopen("tmpfile", "w");

	while (*msg)
		kr_putc(*msg++, fp);
	kr_putc('\n', fp);
	kr_fclose(fp);
	return 0;
}
