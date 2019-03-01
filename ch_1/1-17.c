/*
 * Excercise 1-17. Write a program to print all input lines that are longer
 * than 80 characters 
 */
#include <stdio.h>

#define MAXLINE 1000
#define TRESHOLD 80

int _getline(char line[], int maxline);

main()
{
    int len;
    char line[MAXLINE];
    
    while ((len = _getline(line, MAXLINE)) > 0)
        if (len >= TRESHOLD)
            printf("%s", line);

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
