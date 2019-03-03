// Exercise 2-3. Write the function htoi(s), which converts a string of hexadecimal digits
// (including an optional 0x or 0X) into its equivalent integer value.
// The allowable digits are 0 through 9, a through f, and A through F.

#include <stdio.h>
#include <math.h>
#include <ctype.h>

unsigned long htoi(char[]);

int main()
{
    printf("%s is %lu\n", "100", htoi("100"));
    printf("%s is %lu\n", "", htoi(""));
    printf("%s is %lu\n", "0x", htoi("0x0"));
    printf("%s is %lu\n", "0x100", htoi("0x100"));
    printf("%s is %lu\n", "0X100", htoi("0X100"));
    printf("%s is %lu\n", "3DAD", htoi("3DAD"));
    printf("%s is %lu\n", "0x1744669D5C", htoi("0x1744669D5C"));

    return 0;
}

unsigned long htoi(char s[])
{
    // check for incorrect input
    if (s[0] == '\0')
        return 0;
    
    // find the end of the string
    int i = 0;
    while (s[i+1] != '\0')
        ++i;
    
    int n = 0;
    unsigned long res = 0;
    while (i >= 0)
    {
        if (s[i] >= '0' && s[i] <= '9')
            res += pow(16, n) * (s[i] - '0');
        else if (toupper(s[i]) >= 'A' && toupper(s[i]) <= 'F')
            res += pow(16, n) * (s[i] - '7');
        else if ((s[i] == 'x' || s[i] == 'X') && i == 1 && s[i-1] == '0')
            break;
        else
            return 0;
        --i;
        ++n;
    }
    return res;    
}
