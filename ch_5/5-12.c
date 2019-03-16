// Exercise 5-12. Extend entab and detab to accept the shorthand
//		entab -m +n
// to mean tab stops every n columns, starting at column m. Choose convenient
// default behavior.

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define DEF 4
#define MAXSIZE 100

void detab(char from[], char to[]);
void entab(char from[], char to[]);
int _getline(char s[], int lim);

int M;
int N;

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
				M = atoi(buf);
			}
			else if (*argv[i] == '+')
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
	else // default behavior
	{
		N = 1;
		M = 0;
	}
	
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
		if (from[i] == '\t' && j >= M)
		{
			int jj = j;
			for (int t = 0; t < N-((j-M)%N); ++jj, ++t)
				to[jj] = ' ';
			
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
		while (from[i] == ' ' && j >= M)
		{
			if (i < MAXSIZE && from[i+1] == ' ') // 1 char lookahead
			{
				to[j++] = '\t';
				jj += 2;
				i += 2;
			}
			else //do the alignment to the next tab stop
			{
				int k = N-((jj-M)%N);
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
