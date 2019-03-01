/*
 * Excercise 1-16. Revise the main routine of the longest-line program so
 * it will correctly print the length of arbitrarily long input lines,
 * and as much as possible of the text. 
 */
#include <stdio.h>

#define MAXLINE 10

int _getline(char line[], int maxline);
void copy(char to[], char from[]);

main()
{
    int len;
    int max;
    char line[MAXLINE];
    char longest[MAXLINE];
    
    max = 0;
    while ((len = _getline(line, MAXLINE)) > 0)
        if (len > max)
        {
            max = len;
            copy(longest, line);
        }
    if (max > 0)
    {
        printf("%s\n", longest);
        printf("Length: %d\n", max);
    }
    return 0;
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

void copy(char to[], char from[])
{
    int i = 0;
    
    while ((to[i] = from[i]) != '\0')
        ++i;
}
