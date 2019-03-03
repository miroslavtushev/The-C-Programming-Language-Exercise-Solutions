// Exercise 2-5. Write the function any(s1, s2), which returns the first location in the string s1
// where any character from the string s2 occurs, or -1 if s1 contains no characters from s2.

#include <stdio.h>
#include <limits.h>

int any (char[], char[]);

int main()
{
    char s1[] = "geeksforgeeks";
    char s2[] = "app";
    char s3[] = "kite";
    char s4[] = "hi, walls";
    
    printf("%d\n", any(s1, s2));
    printf("%d\n", any(s1, s3));
    printf("%d\n", any(s1, s4));
    return 0;
}

int any(char s1[], char s2[])
{
    int minCur = INT_MAX;
    int i = -1;
    while (s2[++i] != '\0')
    {
        char c = s2[i];
        int j = -1;
        while (s1[++j] != '\0')
            if (s1[j] == c)
                minCur = j < minCur ? j : minCur;
    }
    if (minCur == INT_MAX)
        return -1;
    else
        return minCur;
}
