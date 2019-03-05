/*
 * Rewrite the routines day_of_year and month_day with pointers instead of indexing.
 */

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
    int leap;
    char *p;

    leap = !(year % 4) && (year % 100) || !(year % 400);
    p = *(daytab + leap);
    while (--month > 0)
        day += *++p;
    return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int leap;
    char *p, *q, *r;

    leap = !(year % 4) && (year % 100) || !(year%400);
    p = q = *(daytab + leap);
    r = p + 13;
    while (++q < r && yearday > *q)
        yearday -= *q;
    *pmonth = q - p;
    *pday = yearday;
}
