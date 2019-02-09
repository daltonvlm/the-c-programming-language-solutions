#include <stdio.h>

int any(char s1[], char s2[])
{
	int i, j;

	for (i = 0; s1[i] != '\0'; i++) {
		for (j = 0; s2[j] != '\0'; j++) {
			if (s2[j] == s1[i]) {
				return i;
			}
		}
	}
	return -1;
}

main()
{
	int i;
	char s1[] = "rio de janeiro";
	char s2[] = " ";

	for (i = 0; s1[i] != '\0'; i++) {
		s2[0] = s1[i];
		printf("'%c' in %d\n", s1[i], any(s1, s2));
	}
	
	return 0;
}
