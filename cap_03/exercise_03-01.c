/*
 * Our binary search makes two tests inside the loop, when one would 
 * suffice (at the price of more tests outside). Write a version with only 
 * one test inside the loop and measure the difference in run-time.
 */

/* binsearch: find x in v[0] <= v[i] <= ... <= v[n-1] */
int binsearch(int x, int v[], int n)
{
	int low, high, mid;
	
	low = 0;
	high = n - 1;
	while (low < high) {
		mid = (low+high) / 2;
		if (x <= v[mid])
			high = mid;
		else
			low = mid + 1;
	}
	mid = (low + high) / 2;
	if (x == v[mid])
		return mid;
	return -1;
}
