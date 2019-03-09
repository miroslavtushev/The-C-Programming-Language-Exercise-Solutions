// Exercise 4-13. Write a recursive version of the function reverse(s), which
// reverses the string s in place.

#include <stdio.h>

void reverse(char s[], int i, int j);
void swap (char s[], int i, int j);

int main()
{
	char s[] = "aabbccddf";
	reverse(s, 0, 0);
	printf("%s\n", s);
	return 0;
}

void reverse(char s[], int i, int j)
{
	if (i == 0) // first call
		j = strlen(s) - 1;
	if (i < j && j-i != 1)
		reverse(s, i+1, j-1);
	swap(s, i, j);
}

void swap (char s[], int i, int j)
{
	int c = s[i];
	s[i] = s[j];
	s[j] = c;
}
