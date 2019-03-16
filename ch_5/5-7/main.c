// Exercise 5-7. Rewrite readlines to store lines in an array supplied by main
// rather than calling alloc to maintain storrage. How much faster is the program?

#include <stdio.h>
#include <string.h>
#include "headers.h"

#define MAXLINES 5000
#define SIZE 10000

char *lineptr[MAXLINES];

int main()
{
	char lines[SIZE]; // instead of alloc
	
	int nlines;
	
	if ((nlines = readlines(lineptr, MAXLINES, lines, SIZE)) >= 0)
	{
		_qsort(lineptr, 0, nlines-1);
		writelines(lineptr, nlines);
		return 0;
	}
	else
	{
		printf("error: input too big to sort\n");
		return 1;
	}
}
