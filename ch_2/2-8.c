// Exercise 2-8. Write a function rightrot(x, n) that returns the value
// of the integer x rotated to the right by n bit positions.

#include <stdio.h>
#define NUM_BITS 32

unsigned rightrot(unsigned x, int n);

int main()
{
    printf("%u\n", rightrot(4677, 4));
    return 0;
}

unsigned rightrot(unsigned x, int n)
{
    return (x >> n) | (x << (NUM_BITS - n));
}
