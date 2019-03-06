// Exercise 3-5. Write a function itob(n,s,b) that converts the integer n into a base
// b character representation in the string s. In particular, itob(n,s,16) formats n
// as a hexadecimal integer s.

#include <stdio.h>
#include <string.h>

void itob(int n, char s[], int b);
void reverse(char s[]);

int main()
{
	char s[100];
	itob(229080596, s, 3);
	
	printf("%s\n", s);
	return 0;
}

void itob(int n, char s[], int b)
{
	int i, sign;
	char baseoffset = '0';
	
	if ((sign=n) < 0)
		n = -n;
	
	i = 0;
	int res;
	do
	{
		res = n % b;
		if (res >= 10)
		{
			baseoffset = 'A';
			res -= 10;
		}
		else
			baseoffset = '0';
		s[i++] = res + baseoffset;
	}
	while ((n /= b) > 0);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

void reverse(char s[])
{
	int c, i, j;
	for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
		c = s[i], s[i] = s[j], s[j] = c;
}
