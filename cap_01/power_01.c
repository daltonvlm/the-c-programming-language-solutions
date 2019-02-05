#include <stdio.h>

/* function prototype */
/* int power(int m, int n); */

/* old-style funtion declaration */
int power();

/* test power function */
main()
{
    int i;

    for (i = 0; i < 10; i++)
        printf("%d %d %d\n", i, power(2, i), power(-3, i));
    return 0;
}

/* power: raise base to the n-th power; n >= 0 */
/*
int power(int base, int n)
{
    int i, p;

    p = 1;
    for (i = 1; i <= n; i++)
        p = p * base;
    return p;
}
*/

/* power: raise base to the n-th power; n >= 0 */
/*        (old-style version) */
power(base, n)
int base, n;
{
    int i, p;

    p = 1;
    for (i = 1; i <= n; i++)
        p = p * base;
    return p;
}
