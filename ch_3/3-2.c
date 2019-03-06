// Exercise 3-2. Write a function escape(s,t) that converts characters like newline and tab
// into visible escape sequences like \n and \t as it copies the string t to s. Use a switch.
// Write a function for the other direction as well, converting escape sequences into
// the real characters.

#include <stdio.h>
#define SIZE 100

void escape(char[], char[]);

int main()
{
    char t[SIZE] = "This	is a line\nThis is		another one\n";
    char s[SIZE];
    escape(s,t);
    printf("%s\n", s);
    return 0;
}

void escape(char s[], char t[])
{
    int i = 0;
    int j = 0;
    char c;
    while ((c = t[i++]) != '\0')
    {
        switch(c)
        {
            case '\n':
                s[j++] = '\\';
                s[j] = 'n';
                break;
            case '\t':
                s[j++] = '\\';
                s[j] = 't';
                break;
            default:
                s[j] = c;
        }
        j++;
    }
    s[j] = '\0';
}
