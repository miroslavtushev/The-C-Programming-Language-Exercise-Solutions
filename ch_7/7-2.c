// Exercise 7-2. Write a program that will print arbitrary input in a sensible way.
// As a minimum, it should print non-graphic characters in octal or hexadecimal
// according to local custom, and break long text lines.

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define WIDTH 30

enum MODE { DEFAULT, OCTAL, HEX} mode = DEFAULT;

void printchars(int mode);

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		argc--;
		if (strcmp(argv[argc], "-o") == 0)
			mode = OCTAL;
		else if (strcmp(argv[argc], "-h") == 0)
			mode = HEX;
		else
		{
			printf("Unknow argument\n");
			return 1;
		}
	}
	else if (argc > 2)
	{
		printf("Unknown argument\n");
		return 1;
	}
	
	printchars(mode);
	
	return 0;
}

void printchars(int mode)
{
	int c, numchars;
	numchars = 0;
	while ((c = getchar()) != EOF && c >= 32 && c <= 126)
	{
		if (mode == DEFAULT)
		{
			putchar(c);
			numchars++;
			if (c == ' ' && numchars >= WIDTH)
			{
				numchars = 0;
				putchar('\n');
			}
		}
		else if (mode == OCTAL)
		{
			printf("%03o ", c);
			numchars++;
			if (c == ' ' && numchars >= WIDTH/3)
			{
				numchars = 0;
				putchar('\n');
			}
		}
		else if (mode == HEX)
		{
			printf("%x ", c);
			numchars++;
			if (c == ' ' && numchars >= WIDTH/2)
			{
				numchars = 0;
				putchar('\n');
			}
		}
	}
	putchar('\n');
}
