// Exercise 2-9. Write a faster version of bitcount.

// By ANDding 2 consequitive bits, you essentially compare the bits they have in common.
// When you substract 1 from x, you invert the last bit in x bc 1 is repr. in binary as 01.
// if x has 1 at the end, substracting 1 will invert that 1 in x. If x has 0 at the end -
// substracting 0 will borrow from the bit on the left of 0 in x, flipping that 1 it borrowed from.

#include <stdio.h>

int bitcount (unsigned x);

int main()
{
    printf("%d\n", bitcount(3));
    return 0;
}

int bitcount (unsigned x)
{
    int b;
    for (b = 0; x != 0; b++)
        x &= (x-1);
    return b;
}
