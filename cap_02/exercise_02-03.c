#include <stdio.h>
#include <ctype.h>

int htoi(char s[])
{
	int n = 0;
	int i = 0;

	if ('0' == s[0] && ('x' == s[1] || 'X' == s[1])) {
		i = 2;
	}
	for (; isxdigit(s[i]); i++) {
		n *= 16;
		if (isdigit(s[i])) {
				n += s[i] - '0';
		} else {
			n += tolower(s[i]) - 'a' + 10;
		}
	}
	return n;
}

main()
{
	printf("%d\n", htoi("0x10"));
	return 0;
}
