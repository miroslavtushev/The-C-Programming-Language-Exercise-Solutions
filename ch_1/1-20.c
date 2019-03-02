/*
 * Exercise 1-20. Write a program detab that replaces tabs in the input with the
 * proper number of blanks to space to the next tab stop. Assume a fixed set of
 * tab stops, say every n columns.
 */

#include <stdio.h>

#define N 2
#define MAXSIZE 1000

void detab(char from[], char to[]);
int _getline(char s[], int lim);

main()
{
    char line[MAXSIZE];
    char replacement[MAXSIZE];
    int len;
    
    while ((len = _getline(line, MAXSIZE)) > 0)
    {
        detab(line, replacement);
        printf("%s", replacement);
    }
}

void detab(char from[], char to[])
{
    int i, j;
    i = j = 0;
    while (from[i] != '\0')
    {
        if (from[i] == '\t')
        {
            int jj = j;
            for (jj; jj < j+N; ++jj)
                to[jj] = ' ';
            j = --jj; // save jj's position
        }
        else
            to[j] = from[i];
        i++;
        j++;
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
