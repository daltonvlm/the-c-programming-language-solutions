#include "syscalls.h"

main()	/* copy input to output */
{
	int n;
	char buf[BUFSIZ];

	while ((n = read(0, buf, BUFSIZ)) > 0)
		write(1, buf, n);
	return 0;
}
