/*
 * Exercise 1-24. Write a program to check a C program for rudimentary syntax errors
 * like unbalanced parentheses, brackets and braces.
 */

#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 10000

#define IN_SINGLE       2
#define IN_MULTI        1
#define OUT_COMMENT     0

#define IN_STRING       1
#define OUT_STRING      0

#define IN_CHAR         1
#define OUT_CHAR        0

int main()
{
    int c;
    int i = 0;
    char input[MAXSIZE];
    
    int comment_state   = OUT_COMMENT;
    int string_state    = OUT_STRING;
    int char_state      = OUT_CHAR;
    
    while ((c = getchar()) != EOF)
    {
        input[i] = c;
        ++i;
    }
    
    int par, brck, brcs;
    int j;
    par = brck = brcs = j = 0;
    while ((c = input[j]) != '\0')
    {
        if (comment_state == IN_MULTI)
        {
            if (c == '*')
            {
                if ((c = input[++j]) == '/')
                    comment_state = OUT_COMMENT;
            }
        }
        else if (comment_state == IN_SINGLE)
        {
            if (c == '\n')
                comment_state = OUT_COMMENT;
        }
        else if (comment_state == OUT_COMMENT && string_state == OUT_STRING && c == '/')
        {
            c = input[++j];
            if (c == '*')
                comment_state = IN_MULTI;
            else if (c == '/')
                comment_state = IN_SINGLE;
        }
        else
        {
            // check for correctness of escape sequences
            if (c == '\\')
            {
                c = input[++j];
                if (c != 'a' ||
                    c != 'b' ||
                    c != 'e' ||
                    c != 'f' ||
                    c != 'n' ||
                    c != 'r' ||
                    c != 't' ||
                    c != 'v' ||
                    c != '\\' ||
                    c != '\'' ||
                    c != '"' ||
                    c != '?' )
                    printf("Incorrect escape sequence\n");
            }
            if (string_state == OUT_STRING && char_state == OUT_CHAR)
            {
                if (c == '"')           string_state = IN_STRING;
                else if (c == '\'')     char_state = IN_CHAR;
                else // check for unbalanced parens
                {
                    if (c == '(')
                        ++par;
                    else if (c == ')')
                        --par;
                    else if (c == '[')
                        ++brck;
                    else if (c == ']')
                        --brck;
                    else if (c == '{')
                        ++brcs;
                    else if (c == '}')
                        --brcs;
                }
            }
            else if (c == '"' && string_state == IN_STRING && char_state == OUT_CHAR)
                string_state = OUT_STRING;
            else if (c == '\'' && char_state == IN_CHAR && string_state == OUT_STRING)
                char_state = OUT_CHAR;
  
        }
        ++j;
    }
    
    /* Printing */
    if (string_state == IN_STRING)
        printf("String has not been terminated\n");
    if (char_state == IN_CHAR)
        printf("Character terminal error\n");
    printf("\n");
    printf("Unbalanced parentheses found: %d\n", abs(par));
    printf("Unbalanced brackets found: %d\n", abs(brck));
    printf("Unbalanced braces found: %d\n", abs(brcs));
}
