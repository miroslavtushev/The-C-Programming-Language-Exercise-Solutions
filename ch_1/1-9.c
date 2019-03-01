/*
 * Exercise 1-9. Write a program to copy its input to its output, replacing
 * each string of one of more blanks by a single blank.
 */

#include <stdio.h>

main()
{
    int c;
    int ws = 0;

    while((c = getchar()) != EOF)
    {
        if (c == ' ') 
        {
            if (ws != 0)
            {
                c = '\0';
            } 
            else 
            {
                ++ws;
            }
        } 
        else 
        {
            ws = 0;          
        }
        putchar(c); 
    }
}
