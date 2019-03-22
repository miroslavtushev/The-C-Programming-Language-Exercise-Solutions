// Exercise 7-1. Write a program that converts upper case to lower case
// to upper, depending on the name it is invoked with, as found in argv[0].

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int strend(const char *s, const char *t);

int main(int argc, char **argv)
{
	int c;
	if (strend(argv[0], "tolower"))
		while ((c = getchar()) != EOF)
			putchar(tolower(c));
	else if (strend(argv[0], "toupper"))
		while ((c = getchar()) != EOF)
			putchar(toupper(c));
	return 0;
}

int strend(const char *s, const char *t)
{
	size_t ls = strlen(s); // find length of s
	size_t lt = strlen(t); // find length of t
	if (ls >= lt)  // check if t can fit in s
	{
		// point s to where t should start and compare the strings from there
		return (0 == memcmp(t, s + (ls - lt), lt));
	}
	return 0; // t was longer than s
}
