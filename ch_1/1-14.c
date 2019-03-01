/*
 * Write a program to print a histogram of the frequencies of different
 * characters in its input.
 */

#include <stdio.h>

#define LEN 100

main()
{
    int nchars[LEN];
    int nlengths[LEN];
    int c;
    
    for (int i = 0; i < LEN; i++)
        nlengths[i] = nchars[i] = 0;
    
    while ((c = getchar()) != EOF)
    {
        if (c != '\n' && c != '\t' && c != ' ')
        {
            int i = 0;
            while (nchars[i] != 0)
            {
                if (nchars[i] == c)
                {
                    nlengths[i]++;
                    break;
                }
                ++i;
            }
            // add new char to array
            if (nchars[i] == 0)
            {
                nchars[i] = c;
                nlengths[i]++;
            }
        }
    }
    
    // printing out histogram
    int i = 0;
    while (nchars[i] != 0)
    {
        printf("%c: ", nchars[i]);
        for (int j = 0; j < nlengths[i]; j++)
            printf("*");
        printf("\n");
        i++;
    }
}
