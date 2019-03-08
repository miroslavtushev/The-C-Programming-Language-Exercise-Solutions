// Exercise 4-1. Write the function strrindex(s,t), which returns the position
// of the rightmost occurance of t in s, or -1 if there's none.

#include <stdio.h>
#define MAXLINE 1000

int _getline(char line[], int max);
int strrindex(char s[], char t[]);

char pattern[] = "ould";

int main()
{
	char line[MAXLINE];
	int found = 0;
	
	while (_getline(line, MAXLINE) > 0)
	{
		int i;
		if ((i = strrindex(line, pattern)) >= 0)
		{
			printf("%sOccured at: %d\n", line, i);
			found++;
		}
	}
    return found;

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

int strrindex(char s[], char t[])
{
	int i, j, k, ret = -1; // change
	
	for (i = 0; s[i] != '\0'; i++)
	{
		for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
			;
		if (k > 0 && t[k] == '\0')
			ret = i; //change
	}
	return ret; //change
}
