#include <stdio.h>
#include "headers.h"

int gettoken(void)
{
	int c;
	extern char token[];
	extern int tokentype;
	extern int savedtoken;
	extern int er;
	char *p = token;
	
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
		return tokentype = NAME;
	}
	else
		return tokentype = c;
}
