// Exercise 7-7.  Modify the pattern finding program of Chapter 5 to take its input
// from a set of named files or, if no files are named as arguments, from the
// standard input. Should the file name be printed when a matching line is found?

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 1000

int main(int argc, char **argv)
{
	char *line;
	char *list_of_files[10];
	char *pat;
	
	FILE *input = stdin;
	
	size_t size = MAXLINE;
	long lineno = 0;
	int i = 0, files = 0, except = 0, number = 0, found = 0, curarg = 0;
	
	while (++curarg < argc)
	{
		if (strcmp(argv[curarg], "-x") == 0)
			except = 1;
		else if (strcmp(argv[curarg], "-n") == 0)
			number = 1;
		else
		{
			if (curarg == (argc-1)) // pattern
				pat = strdup(argv[curarg]);
			else
			{
				files++;
				list_of_files[i++] = strdup(argv[curarg]);
			}
		}
	}
	
	if (argc == 1)
		printf("Usage: find -x -n [file1,[file2,...]] pattern\n");
	else if (!files)
	{
		while (getline(&line, &size, input) > 0)
		{
			lineno++;
			if ((strstr(line, pat) != NULL) != except)
			{
				if (number)
					printf("%ld: ", lineno);
				printf("%s", line);
				found++;
			}
		}
	}
	else
	{
		char line[MAXLINE];
		for (int i = 0; i < files; i++)
		{
			lineno = 0;
			if ((input = fopen(list_of_files[i], "r")) == NULL)
			{
				fprintf(stderr, "Cannot open file: %s\n", list_of_files[i]);
				exit(1);
			}
			while (fgets(line, MAXLINE, input) != NULL)
			{
				lineno++;
				if ((strstr(line, pat) != NULL) != except)
				{
					if (number)
						printf("%ld: ", lineno);
					printf("%s: %s", list_of_files[i], line);
					found++;
				}
			}
			fclose(input);
		}
	}
	return found;
}
