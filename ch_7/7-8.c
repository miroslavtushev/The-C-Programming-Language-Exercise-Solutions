// Exercise 7-8. Write a program to print a set of files, starting each new one on a
// new page, with a title and a running page count for each file.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 1000
#define LINESPERPAGE 20

int main(int argc, char **argv)
{
	char *list_of_files[10];
	char line[MAXLINE];
	int curline, page = 1, curarg = 0;
	FILE *fp;

	while (++curarg < argc)
		list_of_files[curarg-1] = strdup(argv[curarg]);
	
	for (int i = 0; i < curarg; i++)
	{
		curline = 0;
		if ((fp = fopen(list_of_files[i], "r")) == NULL)
		{
			fprintf(stderr, "Cannot open file: %s\n", list_of_files[i]);
			continue;
		}
		printf("%s\n", list_of_files[i]);
		for (int j = 0; list_of_files[i][j] != '\0'; j++)
			printf("-");
		printf("\n");
		while (fgets(line, MAXLINE, fp) != NULL)
		{
			curline++;
			printf("%s", line);
			if (curline > LINESPERPAGE)
			{
				curline = 0;
				printf("Page %d\n-------\n\n", page++);
			}
		}
		for (; curline < LINESPERPAGE; curline++)
			printf("\n");
		printf("Page %d\n-------\n\n", page++);
		fclose(fp);		
	}
	return 0;
}
