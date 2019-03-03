// Exercise 2-6. Write a function setbits(x,p,n,y) that returns x with the n
// bits that begin at the position p set to the rightmost n bits of y,
// leaving the other bits unchanged.

#include <stdio.h>
#include <limits.h>

unsigned setbits(unsigned x, int p, int n, unsigned y);

int main()
{
    printf("%u\n", setbits(349, 5, 3, 57));
    return 0;
}

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
    // 1. create a mask for y to extract the leftmost bits
    unsigned my = ~(~0 << n);
    // 2. apply it to y and shift y in the position (the required bits are now aligned)
    y = ((y & my) << (p+1-n));
    // 3. create a mask for x to get the "tail"
    unsigned mx = ~(~0 << (p+1-n));
    // 4. extract the tail from x
    mx = mx & x;
    // 5. merge the required bits and tail
    return y | mx;
}
