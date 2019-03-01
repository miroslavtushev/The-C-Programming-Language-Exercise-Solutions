/*
 * Exercise 1-3, 1-4. 
 */
#include <stdio.h>

main() 
{
    float fahr, cels;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    fahr = lower;

    printf("Celcius to Farenheit Conversion Table\n");
    while (fahr <= upper)
    {
        cels = (5.0/9.0) * (fahr - 32.0);
        printf("%6.2f %6.0f\n", cels, fahr);
        fahr += step;
    }
}
