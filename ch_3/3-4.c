// Exercise 3-4. In a two's complement number system representation, our version
// of itoa does not handle the largest negative number, that is, the value of n
// equal to -( 2^(wordsize-1) ). Explain why not. Modify it to print that value
// correctly, regardless of the machine on which it runs.

// that's because the absolute value of the maximum 32bit INT is 1 greater
// than the absolute value of the minimum 32bit INT. When we do "n = -n" for
// the INT_MIN, an overflow occurs and the value "slides back" to the value-1,
// which is exactly the same INT_MIN due to the circular nature of the 2 complement's
// numbers in the computer.

#include <stdio.h>
#include <string.h>
#include <limits.h>

void itoa(int n, char s[]);
void reverse(char s[]);

int main()
{
	char s[10];
	itoa(INT_MIN, s);

	printf("%s\n", s);
	return 0;
}

void itoa(int n, char s[])
{
	int i, sign, offset = 0;
	
	if ((sign=n) < 0)
	{
		if (n == INT_MIN)
		{
			n += 1;
			offset = 1;
		}
		n = -n;
	}
	i = 0;
	do
	{
		s[i++] = n % 10 + '0';
	}
	while ((n /= 10) > 0);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
	
	// add offset if needed
	if (offset)
	{
		if (s[i-1] != '9')
			s[i-1]++;
		else
		{
			s[i-1] = '1';
			s[i] = '0';
			s[i+1] = '\0';
		}
	}
}

void reverse(char s[])
{
	int c, i, j;
	for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
		c = s[i], s[i] = s[j], s[j] = c;
}
