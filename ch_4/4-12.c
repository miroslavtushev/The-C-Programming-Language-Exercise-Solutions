// Exercise 4-12. Adapt the ideas of printd to write a recursive version of itoa;
// that is, convert an integer into a string by calling a recursive routine.

#include <stdio.h>

void itoa(int n);

int main()
{
	itoa(-345);
    
	return 0;
}

void itoa(int n)
{
	if (n < 0)
	{
		putchar('-');
		n = -n;
	}
	
	if (n > 10)
		itoa(n/10);
	putchar(n % 10 + '0');
}
