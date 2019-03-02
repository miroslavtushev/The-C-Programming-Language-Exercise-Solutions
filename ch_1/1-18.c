/*
 * Excercise 1-18. Write a program to remove trailing blanks and tabs
 * from each line of input, and to delete entirely blank lines.
 */
#include <stdio.h>

#define MAXLINE 1000

int _getline(char line[], int maxline);
int findTrailingBlanks(char input[], int len);

main()
{
    int len;
    char line[MAXLINE];
    char result[MAXLINE];
    
    while ((len = _getline(line, MAXLINE)) > 0)
    {
        int idx = findTrailingBlanks(line, len);
        if (idx == 0) // blank line
            continue;
        line[++idx] = '\n';
        line[++idx] = '\0';
        printf("%s", line);
    }
    
    return 0;
}

int _getline(char s[], int lim)
{
    int c, i;
    
    i = 0;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n')
    {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

/* finds the last char index */
int findTrailingBlanks(char input[], int len)
{
    int i = len;
    while (i > 0)
    {
        if (input[i] == ' ' || input[i] == '\t'
            || input[i] == '\n' || input[i] == '\0')
        {
            i--;
        }
        else
            return i;
    }
    return i;
}
