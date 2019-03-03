// Exercise 2-7. Write a function invert(x, p, n) that returns x with the n bits
// that begin at position p inverted (i.e., 1 changed into 0 and vice versa),
// leaving the others unchanged.

#include <stdio.h>

unsigned invertOriginal(unsigned x, int p, int n);
unsigned invertImproved(unsigned x, int p, int n);

int main()
{
    printf("%u\n", invertOriginal(3977, 6, 3));
    printf("%u\n", invertImproved(3977, 6, 3));
    return 0;
}

unsigned invertOriginal(unsigned x, int p, int n)
{
    // 1. extract the tail from x using a mask
    unsigned tail = ~(~0 << (p+1-n)) & x;
    // 2. extract the mid
    unsigned mid = ~(~0 << n) << (p+1-n) & x;
    // 2.1 shift in the rightmost position, invert,
    // apply the mask to keep the n bits, and shift
    // back onto original mid position. The actual inversion
    // happens here.
    mid = (~(mid >> (p+1-n)) & ~(~0 << n)) << (p+1-n);
    // 3. extract the front part
    unsigned front = ~0 << (p+1) & x;
    // 4. combine them all together
    return ((0 | front) | mid) | tail;
}

unsigned invertImproved(unsigned x, int p, int n)
{
    // creating a mask in a hop
    unsigned mask = ~(~0 << (p+1)) & (~0 << (p+1-n));
    return (x & ~mask) | (~x & mask);
}

