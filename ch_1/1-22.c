/*
 * Exercise 1-22. Write a program to fold long input lines into two or more shorter
 * lines after the last non-blank character that occurs before the n-th column of
 * input.
 */

#include <stdio.h>

#define MAXSIZE 1000
#define N 10

//finds the position i of the last non-blank char, where i < N
int findNonblankIdx (char input[], int start); //
// cuts input of specified length
void cut(char input[], char output[], int start, int length);
int _getline(char s[], int lim);

main()
{
    char line[MAXSIZE];
    char replacement[MAXSIZE];
    int len;
    
    while ((len = _getline(line, MAXSIZE)) > 0)
    {
        int i = len;
        int start = 0;
        while(i > 0)
        {
            // find next non-blank starting position
            while (line[start] == ' ' || line[start] == '\t')
                start++;
            
            int length = findNonblankIdx(line, start);
            if (length != -1)
            {
                cut(line, replacement, start, length);
                printf("%s", replacement);
                start = start+length+1;
                i -= length;
            }
            else
                break;
        }
    }
    
}

int findNonblankIdx(char input[], int start)
{
    int i = N + start;
    int j = N + start;
    for (i; i > start; i--)
    {
        if (input[i] == ' ' || input[i] == '\t' || input[i] == '\0')
        {
            while (input[i] == ' ' || input[i] == '\t' || input[i] == '\0')
            {
                j = --i;
            }
            return j - start;
        }
    }
    return -1; // too long line
}

void cut(char input[], char output[], int start, int length)
{
    int i,j;
    i = j = 0;
    for (i; i <= length; i++)
        output[i] = input[i + start];

    output[i] = '\n';
    output[++i] = '\0';
    
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
