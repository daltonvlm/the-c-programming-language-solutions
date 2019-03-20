/*
 * Write the function strindex(s, t), which returns the position of the 
 * rightmost occurence of t in s, or -1 if there is none.
 */

int strindex(char source[], char searchfor[])
{
	int i, j, pos;

	pos = -1;
	for (i = 0; source[i] != '\0'; i++) {
		for (j = 0; searchfor[j] != '\0' && searchfor[j] == source[i + j]; j++) {
			;
		}
		if (j > 0 && '\0' == searchfor[j]) {
			pos = i;
		}
	}
	return pos;
}
