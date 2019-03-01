/*
 * Exercise 1-12. Write a program that prints its input one word per line. 
 */

#include <stdio.h>

#define IN 1
#define OUT 0

main()
{
    int c;
    int state = OUT;

    while ((c = getchar()) != EOF)
    {
        if (state == IN)
        {
            if (c != '\n' && c != '\t' && c != ' ')
            {
                putchar(c);
            }
            else
            {
                putchar('\n');
                state = OUT;
            }
        }
        else if ((state == OUT) && (c != '\n' && c != '\t' && c != ' '))
        {
            putchar(c);
            state = IN;
        }
    }
}
