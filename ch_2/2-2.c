// Exercise 2-2. Write a loop equivalent to the for loop above without using
// && or ||.

#include <stdio.h>

int main()
{
    int i = 0;;
    char c;
    int lim = 100;
    char s[lim];

    while ((c=getchar()) != '\n')
    {
        if (c != EOF)
            if (i < lim-1)
            {
                s[i] = c;
                ++i;
            }
        
    }
    return 0;
}
