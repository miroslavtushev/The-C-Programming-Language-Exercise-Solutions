#include <stdio.h>
#include <string.h>
#include "headers.h"
#define MAXLEN 1000

int readlines(char *lineptr[], int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];
	extern int N;
	
	nlines = 0;
	while ((len = _getline(line, MAXLEN)) > 0)
		if ((p = alloc(len)) == NULL)
			return -1;
	else
	{
		line[len-1] = '\0';
		strcpy(p, line);
		lineptr[nlines%N] = p;
		nlines++;
	}
	return nlines;
}

void writelines(char *lineptr[], int nlines)
{
	extern int N;
	int i;
	
	if (nlines > N)
	{
		i = nlines;
		nlines = N;
	}
	else
		i = 0;
	
	int j = 0;
	while (j++ < nlines)
	{
		printf("%s\n", lineptr[i%N]);
		i++;
	}	
}

int _getline(char s[], int lim)
{
	int c, i;
	
	i = 0;
	while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}


