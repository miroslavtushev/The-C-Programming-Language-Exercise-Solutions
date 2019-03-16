// Exercise 5-14 - 17.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "headers.h"

#define DEFAULT strcmp
#define NUMBER numcmp
#define DIRECTORY dircmp

#define MAXLINES 5000
#define SIZE 100
char *lineptr[MAXLINES];

int main(int argc, char **argv)
{
	int nlines;
	int reverse = 1;
	int casefold = 0;
	
	// for fields
	int k_sort = 0;
	int k_reverse = 1;
	int k_casefold = 0;
	
	int (*cmptype)(void*, void*) = DEFAULT;
	int (*k_cmptype)(void*, void*) = DEFAULT;
	
	int a = 1;
	while (a < argc)
	{
		if (strcmp(argv[a], "-k") == 0)
		{
			k_sort = 1;
			int i = 0;
			char *arg = argv[++a];
			while (arg[i])
			{
				if (arg[i] == 'n')
					k_cmptype = NUMBER;
				else if (arg[i] == 'r')
					k_reverse = -1;
				else if (arg[i] == 'f')
					k_casefold = 1;
				else if (arg[i] == 'd')
					k_cmptype = DIRECTORY;
				i++;
			}
		}
		else if (strcmp(argv[a], "-n") == 0)
			cmptype = NUMBER;
		else if (strcmp(argv[a], "-r") == 0)
			reverse = -1;
		else if (strcmp(argv[a], "-f") == 0)
			casefold = 1;
		else if (strcmp(argv[a], "-d") == 0)
			cmptype = DIRECTORY;
		a++;
	}
	
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0)
	{
		_qsort((void **) lineptr, 0, nlines-1, cmptype, reverse, casefold);
		if (k_sort) // if sortinf by fields was requested
		{
			// for each line of input
			for (int i = 0; i < nlines; i++)
			{
				char line[SIZE];
				char *fieldslist[MAXLINES];
				int j = 0;

				strcpy(line, lineptr[i]);
				
				// tokenize the line
				// skip first one
				char *initial = strtok(line, " ");
				char *tok = strtok(NULL, " ");
				while (tok != NULL)
				{
					strcpy(fieldslist[j++], tok);
					tok = strtok(NULL, " ");
				}
				
				// sort the array
				_qsort((void **) fieldslist, 0, j-1, k_cmptype, k_reverse, k_casefold);
				// append back
				strcat(initial, " ");
				for (int k = 0; k < j; k++)
				{
					strcat(initial, fieldslist[k]);
					strcat(initial, (k < j - 1) ? " " : "");
				}
				strcpy(lineptr[i], initial);
			}
			
		}
		writelines(lineptr, nlines);
		return 0;
	}
	else
	{
		printf("input too big to sort\n");
		return 1;
	}
}
