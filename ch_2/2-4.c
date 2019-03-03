// Exercise 2-4. Write an alternate version of squeeze(s1,s2) that deletes
// each character in s1 that matches any character in the string s2.

#include <stdio.h>

void squeeze(char[], char[]);

int main()
{
    char s1[] = "aabbagis";
    char s2[] = "saibab";
    squeeze(s1, s2);
    printf("%s\n", s1);
    return 0;
}

void squeeze(char s1[], char s2[])
{
    int i = -1;
    while (s1[++i] != '\0')
    {
        int j = -1;
        while (s2[++j] != '\0')
        {
            if (s1[i] == s2[j])
            {
                // shift all elements starting from i+i to i
                int k = i;
                while (s1[k++] != '\0')
                    s1[k-1] = s1[k];
                j--;
                i = -1; // restart s1's counter
            }
        }
    }
}
