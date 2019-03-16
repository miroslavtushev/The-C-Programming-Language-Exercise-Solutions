// Exercise 5-3. Write a pointer version of the function strcat that we showed
// in CHapter 2: strcat(s,t) copies the string t to the end of s.

#include <stdio.h>
#define MAXSZ 100

void _strcat(char *s, char *t);

int main()
{
	char a[MAXSZ] = "This is one string. ";
	char b[MAXSZ] = "And this is another.";
	_strcat(a, b);
	printf("%s\n", a);
	return 0;
}

void _strcat(char *s, char *t)
{
	while (*s++)
		;
	*s--;
	while (*s++ = *t++)
		;
}
