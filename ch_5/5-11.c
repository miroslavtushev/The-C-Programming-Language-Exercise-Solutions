// Exercise 5-11. Modify the programs entab and detab to accept a list of
// tab stops as arguments. Use the default tab settings if there are
// no arguments.

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define DEF 4
#define MAXSIZE 100

void detab(char from[], char to[]);
void entab(char from[], char to[]);
int _getline(char s[], int lim);

int tabstops[100] = { 0 };

int main(int argc, char **argv)
{
	int i = 0;
	while (++i < argc)
		tabstops[i-1] = atoi(argv[i]);
	
	char line[MAXSIZE];
	char replacement[MAXSIZE];
	
	_getline(line, MAXSIZE);
	
	entab(line, replacement);
	printf("%s", replacement);
	
	return 0;
}

void detab(char from[], char to[])
{
	int i, j, curtab;
	i = j = curtab = 0;
	while (from[i] != '\0')
	{
		if (from[i] == '\t')
		{
			int jj = j;
			int tab = 0;
			// find next tabstop
			int k = 0;
			while (k < 99 && jj >= tabstops[k])
				tab = tabstops[++k];
			if (tab == 0) // default behavior
			{
				tab = DEF;
				for (int t = 0; t < tab-(j%tab); ++jj, ++t)
					to[jj] = ' ';
			}
			else
			{
				for (int t = 0; t < tab%j; ++jj, ++t)
					to[jj] = ' ';
			}
			j = --jj;
		}
		else
			to[j] = from[i];
		i++;
		j++;
	}
	to[j] = '\0';
}

void entab(char from[], char to[])
{
	int i, j, jj;
	i = j = jj = 0;
	while (from[i] != '\0')
	{
		while (from[i] == ' ')
		{
			if (i < MAXSIZE && from[i+1] == ' ') // 1 char lookahead
			{
				to[j++] = '\t';
				jj += 2;
				i += 2;
			}
			else //do the alignment to the next tab stop
			{
				// find next tabstop
				int e = 0;
				int tab = 0;
				while (e < 99 && jj >= tabstops[e])
					tab = tabstops[++e];
				
				int k;
				if (!tab)
				{
					tab = DEF;
					k = tab%jj;
				}
				else
					k = tab-(jj%tab);
				while(k > 0)
				{
					if (k >= 2)
					{
						to[j++] = '\t';
						jj += 2;
						k -= 2;
					}
					else
					{
						to[j++] = ' ';
						jj++;
						k--;
					}
				}
				i++;
			}
		}
		to[j] = from[i];
		i++;
		j++;
		jj++;
	}
	to[j] = '\0';
}

int _getline(char s[], int lim)
{
	int c, i, len;
	len = 0;
	i = 0;
	
	while ((c = getchar()) != EOF && c != '\n')
	{
		++len;
		if (i < lim - 2)
		{
			s[i] = c;
			++i;
		}
	}
	
	if (c == '\n')
	{
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return len;
}
