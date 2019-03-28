/*
 * Write a function expand(s1, s2) that expands shorthand notations like 
 * a-z in the string s1 into the equivalent complelte list abc ... xyz in 
 * s2. Allow for letters of either case and digits, and be prepared to 
 * handle cases like a-b-c and a-z0-9 and -a-z. Arrange that a leading or 
 * trailing - is taken literally.
 */

int isgap(int prev, int next, int min, int max)
{
	return prev >= min && prev <= max &&
		   next >= min && next <= max &&
		   prev <= next;
}

void expand(char s1[], char s2[])
{
	int i, j, c, prev, next;

	for (i=0, j=0; s1[i] != '\0'; i++) {
		if (i>0 && '-'==s1[i]) {
			prev = s1[i-1];
			next = s1[i+1];

			if (isgap(prev, next, '0', '9') ||
					isgap(prev, next, 'a', 'z') ||
					isgap(prev, next, 'A', 'Z')) {

				for (c = prev + 1; c < next; c++) {
					s2[j++] = c;
				}
				i++;
			}
		}
		s2[j++] = s1[i];
	}
	s2[j] = '\0';
}
