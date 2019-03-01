/*
 * Excercise 1-19. Write a function reverse(s) that reverses the
 * character string s. Use it to write a program that reverses its
 * input a line at a time. 
 */
#include <stdio.h>

#define MAXLINE 1000

int _getline(char line[], int maxline);
void copy(char to[], char from[]);
void reverse(char s[]);

main()
{
    int len;
    char line[MAXLINE];
    
    while ((len = _getline(line, MAXLINE)) > 0)
    {
        reverse(line);
        printf("%s", line);
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

void reverse(char s[])
{
    // find the length of s
    int len = 0;
    for (len; s[len] != '\0'; ++len)
        ;
    char reversed[len];
    len -= 2; // skip \0 and \n
    int i = 0;
    while (len >= 0)
    {
        reversed[i] = s[len];
        ++i;
        --len;
    }
    reversed[i] = '\n';
    reversed[++i] = '\0';
    // copy back to the original array
    copy(s, reversed);
}

void copy(char to[], char from[])
{
    int i = 0;
    
    while ((to[i] = from[i]) != '\0')
        ++i;
}
