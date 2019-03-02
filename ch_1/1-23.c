/*
 * Exercise 1-23. Write a program to remove all comments from a C program.
 *
 */

#include <stdio.h>

#define IN_SINGLE       2
#define IN_MULTI        1
#define OUT_COMMENT     0

#define IN_STRING       1
#define OUT_STRING      0

#define IN_CHAR         1
#define OUT_CHAR        0

main()
{
    int c;
    int comment_state   = OUT_COMMENT;
    int string_state    = OUT_STRING;
    int char_state      = OUT_CHAR;
    
    while ((c = getchar()) != EOF)
    {
        if (comment_state == IN_MULTI)
        {
            if (c == '*')
            {
                if ((c = getchar()) == '/')
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
            c = getchar();
            if (c == '*')
                comment_state = IN_MULTI;
            else if (c == '/')
                comment_state = IN_SINGLE;
        }
        else
        {
            if (c == '"' && string_state == OUT_STRING && char_state == OUT_CHAR)
                string_state = IN_STRING;
            else if (c == '"' && string_state == IN_STRING && char_state == OUT_CHAR)
                string_state = OUT_STRING;
            else if (c == '\'' && char_state == OUT_CHAR && string_state == OUT_STRING)
                char_state = IN_CHAR;
            else if (c == '\'' && char_state == IN_CHAR && string_state == OUT_STRING)
                char_state = OUT_CHAR;
            putchar(c);
        }
    }
}
