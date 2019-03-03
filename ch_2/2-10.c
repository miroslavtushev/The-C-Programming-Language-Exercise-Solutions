// Exercise 2-10. Rewrite the function lower with a conditional expression
// instead of if-else

#include <stdio.h>

int lower (int c);

int main()
{
    printf ("%c\n", lower('A'));
    printf ("%c\n", lower('c'));
    return 0;
}

int lower (int c)
{
    return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}
