// Exercise 7-6. Write a program to compare two files, printing the first line
// where they differ.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSTRING 1000

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		fprintf(stderr, "Wrong number of arguments: %d. Need 2.", argc);
		exit(1);
	}
	FILE *fp1;
	FILE *fp2;
	
	if ((fp1 = fopen(*++argv, "r")) == NULL || (fp2 = fopen(*++argv, "r")) == NULL)
	{
		fprintf(stderr, "Cannot open file: %s\n", *argv);
		exit(1);
	}
	
	char str1[MAXSTRING];
	char str2[MAXSTRING];

	while (1)
	{
		if (fgets(str1, MAXSTRING, fp1) == NULL)
		{
			printf("File 2: %s", str2);
			return 0;
		}

		if (fgets(str2, MAXSTRING, fp2) == NULL)
		{
			printf("File 1: %s", str1);
			return 0;
		}
		
		if (strcmp(str1,str2) != 0)
		{
			printf("File 1: %s", str1);
			printf("File 2: %s", str2);
			return 0;
		}
	}
	return 0;
}
