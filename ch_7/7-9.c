// Exercise 7-9. Functions like isupper can be implemented to save space or to
// save time. Explore both possibilities.

#include <stdio.h>
#define __isupper(c) ((c) >= 65 && (c) <= 90) ? 1 : 0

int _isupper(int c);

int main()
{
	printf("%d\n", _isupper('a'));
	printf("%d\n", __isupper('A'));
	return 0;
}

int _isupper(int c)
{
	return c >= 65 && c <= 90;
}
