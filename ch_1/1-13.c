/*
 * Exercise 1-13. Write a program to print a histogram of the lengths of words
 * in its input. It is easy to draw the histogram with bars horizontal;
 * a vertical orientation is more challenging. 
 */

#include <stdio.h>

#define MAXLEN 10

main()
{
    int nletters[MAXLEN];
    int curLen = 0;
    int c;
    
    for (int i = 0; i < MAXLEN; i++)
        nletters[i] = 0;
    
    while ((c = getchar()) != EOF)
    {
        if (c == '\n' || c == '\t' || c == ' ') // stop counting
        {
            ++nletters[curLen];
            curLen = 0;
        }
        else
        {
            ++curLen;
        }
    }
    
    // printing out historgram
    for (int i = 1; i < MAXLEN; i++)
    {
        printf("%2d: ", i);
        for (int j = 0; j < nletters[i]; j++)
            printf("*");
        printf("\n");
    }
}
