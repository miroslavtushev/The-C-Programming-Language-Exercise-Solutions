#include <stdio.h>
#include <string.h>
#include "headers.h"

int gettoken(void)
{
	int c;
	extern char token[];
	extern char modifier[];
	extern int tokentype;
	extern int savedtoken;
	extern int er;
	
	char buffer[100];
	char *p = buffer;
	
	if (er)
	{
		er = 0;
		return savedtoken;
	}
	
	while ((c = getch()) == ' ' || c == '\t')
		;
	if (c == '(')
	{
		if ((c = getch()) == ')')
		{
			strcpy(token, "()");
			return tokentype = PARENS;
		}
		else
		{
			_ungetch(c);
			return tokentype = '(';
		}
	}
	else if (c == '[')
	{
		for (*p++ = c; (*p++ = getch()) != ']';)
			;
		*p = '\0';
		return tokentype = BRACKETS;
	}
	else if (isalpha(c))
	{
		for (*p++ = c; isalnum(c = getch());)
			*p++ = c;
		*p = '\0';
		_ungetch(c);
		if ((strcmp(buffer, "const")) == 0)
			return tokentype = MODIFIER;
		else if ((strcmp(buffer, "char")) == 0 || (strcmp(buffer, "int")) == 0)
		{
			strcpy(token, buffer);
			return tokentype = NAME;
		}
		else
		{
			{
				strcpy(token, buffer);
				return tokentype = NAME;
			}
		}
	}
	else
		return tokentype = c;
}
