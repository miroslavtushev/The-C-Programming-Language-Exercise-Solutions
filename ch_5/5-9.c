// Exercise 5-9. Rewrite the routines day_of_year and month_day with
// pointers instead of indexing.

#include <stdio.h>

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

static char daytab[2][13] =
{
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int main()
{
	int month, day;
	month = day = 0;
	
	printf("%d\n", day_of_year(1988, 12, 3));
	printf("%d\n", day_of_year(2007, 0, 5));
	
	month_day(2008, 67, &month, &day);
	printf("%d %d\n", month, day);
	month_day(-30, 100, &month, &day);
	printf("%d %d\n", month, day);
	
	
	return 0;
}

int day_of_year(int year, int month, int day)
{
	// error-checking
	if (year <= 0 || month <= 0 || month > 12 || day < 0 || day > 31)
		return -1;
	char *p;
	int i, leap;
	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	for (i = 1; i < month; i++)
	{
		p = daytab[leap] + i;
		day += *p;
	}
	return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday)
{
	// error-checking
	if (year <= 0 || yearday < 0 || yearday > 365)
		return;
	char *p;
	int i, leap;
	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	for (i = 1; yearday > daytab[leap][i]; i++)
	{
		p = daytab[leap] + i;
		yearday -= *p;
	}
	*pmonth = i;
	*pday = yearday;
}
