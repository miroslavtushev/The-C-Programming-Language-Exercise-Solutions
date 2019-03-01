/*
 * Exercise 1-8. Write a program to count blanks, tabs, and newlines.
 */

#include <stdio.h>

main()
{
    int c, nl, t, b;
    nl = t = b = 0;

    while((c= getchar()) != EOF)
    {
        if (c == '\n')
            ++nl;
        if (c == '\t')
            ++t;
        if (c == ' ')
            ++b;
    }

    printf("new lines: %d\ntabs: %d\nwhite spaces: %d\n", nl, t, b);
}
