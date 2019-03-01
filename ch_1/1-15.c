/*
 * Exercise 1-15. Rewrite the temperature conversion program of Section 1.2
 * to use a function for conversion.
 */

#include <stdio.h>

#define MIN 0
#define MAX 300
#define STEP 20

float farenheitToCelcius (int fahr);

main()
{
    int cel;
    
    for (cel = MIN; cel <= MAX; cel += STEP)
    {
        printf("%3d %6.1f\n", cel, farenheitToCelcius(cel));
    }
}

float farenheitToCelcius (int fahr)
{
    return (5.0/9.0)*(fahr-32);
}
