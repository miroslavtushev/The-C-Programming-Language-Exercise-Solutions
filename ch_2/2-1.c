// Exercise 2-1. Write a program to determine the ranges of char, short,
// int, and long variables, both signed and unsigned, by printing
// appropriate values from standard headers and by direct computation.

#include <stdio.h>
#include <limits.h>

int main()
{
    printf("%-20s %6d %6d\n", "Char signed:", SCHAR_MIN, SCHAR_MAX);
    printf("%-20s %6u %6u\n", "Char unsigned:", 0, UCHAR_MAX);
    printf("%-20s %6d %6d\n", "Short signed:", SHRT_MIN, SHRT_MAX);
    printf("%-20s %6u %6u\n", "Short unsigned:", 0, USHRT_MAX);
    printf("%-20s %6d %6d\n", "Int signed:", INT_MIN, INT_MAX);
    printf("%-20s %6u %6u\n", "Int unsigned:", 0, UINT_MAX);
    printf("%-20s %6ld %6ld\n", "Long signed:", LONG_MIN, LONG_MAX);
    printf("%-20s %6lu %6lu\n", "Long unsigned:", 0, ULONG_MAX);
    printf("\n");
    
    // to find thru direct computation, increment the value until overflow occurs
    char c_min = 0;
    unsigned char cu = -1;
    short s_min = 0;
    unsigned short su = -1;
    int i_min = 0;
    unsigned int iu = -1;
    long l_min = 0;
    unsigned long lu = -1;
    
    for (c_min; c_min >= 0; ++c_min)
        ;
    char c_max = c_min - 1;
    for (s_min; s_min >= 0; ++s_min)
        ;
    short s_max = s_min - 1;
    for (i_min; i_min >= 0; ++i_min)
        ;
    //for (l; l > -1; ++l) // takes too much time on my machine
      //  ;
    
    printf("%-40s %6d %6d\n", "Char signed (by computation):", c_min, c_max);
    printf("%-40s %6u %6u\n", "Char unsigned (by computation):", 0, cu);
    printf("%-40s %6d %6d\n", "Short signed (by computation):", s_min, s_max);
    printf("%-40s %6u %6u\n", "Short unsigned (by computation):", 0, su);
    printf("%-40s %6d %6d\n", "Int signed (by computation):", i_min, i_min-1);
    printf("%-40s %6u %6u\n", "Int unsigned (by computation):", 0, iu);
    printf("%-40s %6ld %6ld\n", "Long signed (by computation):", l_min, l_min-1);
    printf("%-40s %6lu %6lu\n", "Long unsigned (by computation):", 0, lu);
    return 0;
}

