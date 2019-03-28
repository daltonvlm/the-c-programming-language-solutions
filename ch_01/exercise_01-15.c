/*
 * Rewrite the temperature conversion program of Section 1.2 to use a 
 * function for conversion.
 */

#include <stdio.h>

int fahr_celsius(int fahr);

/* print Fahrenheit-Celsius table
    for fahr = 0, 20, ..., 300 */
main()
{
    int fahr, celsius;
    int lower, upper, step;

    lower = 0;      /* lower limit of temperature table */
    upper = 300;    /* upper limit */
    step = 20;      /* step size */

    fahr = lower;
    while (fahr <= upper) {
        celsius = fahr_celsius(fahr);
        printf("%3d %6d\n", fahr, celsius);
        fahr = fahr + step;
    }
}

int fahr_celsius(int fahr)
{
    return 5 * (fahr-32) / 9;
}
