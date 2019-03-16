// Exercise 5-19. Modify undcl so that it does not add redundant parentheses to
// declarations.

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "headers.h"

#define MAXTOKEN 100


int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];

int main()
{
	int type = 0;
	char temp[MAXTOKEN];
	int lookahead;
	int p = 0;
	
	while (gettoken() != EOF)
	{
		strcpy(out, token);
		while (type != '\n')
		{
			if (p)
			{
				p = 0;
				type = lookahead;
			}
			else
				type = gettoken();
			
			if (type == PARENS || type == BRACKETS)
				strcat(out, token);
			else if (type == '*')
			{
				// here check the next one
				p = 1;
				if ((lookahead = gettoken()) == NAME ) // we don't need parens
					sprintf(temp, "*%s", out);
				else
					sprintf(temp, "(*%s)", out);
				strcpy(out, temp);
			}
			else if (type == NAME)
			{
				sprintf(temp, "%s %s", token, out);
				strcpy(out, temp);
			}
			else if (type == 10)
				break;
			else
				printf("invalid input at %s\n", token);
		}
		printf("%s\n", out);
	}
	return 0;
}
