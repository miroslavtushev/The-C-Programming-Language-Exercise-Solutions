/*
 * Exercise 1-21. Write a program entab that replaces strings of blanks by the
 * minimum number of blanks and tabs to achieve the same spacing. Use the same
 * tab stops as for detab.
 */

#include <stdio.h>

#define MAXSIZE 1000
#define N 4

void entab(char from[], char to[]);
int _getline(char s[], int lim);

main()
{
    char line[MAXSIZE];
    char replacement[MAXSIZE];
    int len;
    
    while ((len = _getline(line, MAXSIZE)) > 0)
    {
        entab(line, replacement);
        printf("%s", replacement);
    }
    
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
				int k = N-(jj%N);
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
