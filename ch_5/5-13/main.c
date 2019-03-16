// Exercise 5-13. Write the program tail, which prints the last n lines of its
// input. By default, n is 10, let us say, but it can be changed by an optional
// argument, so that
//		tail -n
// prints the last n lines. The program should behave rationally no matter how
// unreasonable the input or the value of n. Write the program so it makes the
// best use of available storage; lines should be stored as in the sorting program of
// Section 5.6, not in a two-dimensional array of fixed size.

#include <stdio.h>
#include <string.h>
#include "headers.h"

#define MAXSIZE 10

int N = 10;

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		int i = 0;
		char buf[MAXSIZE];
		while (++i < argc)
		{
			if (*argv[i] == '-')
			{
				int j = 0;
				while (buf[j++] = *++argv[i])
					;
				N = atoi(buf);
			}
			else
			{
				printf("Wrong argument\n");
				return -1;
			}
		}
	}
	
	int nlines;
	char *lineptr[N];
	
	if ((nlines = readlines(lineptr, N)) >= 0)
	{
		writelines(lineptr, nlines);
		return 0;
	}
	else
	{
		printf("error: bad input\n");
		return 1;
	}
}

