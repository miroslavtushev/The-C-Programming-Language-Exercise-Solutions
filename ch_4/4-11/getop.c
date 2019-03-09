#include <stdio.h>
#include <ctype.h>
#include "calc.h"

int ch = 0;

int getop(char s[])
{
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t') // skipping whitespaces
		;
	
	s[1] = '\0';
	
	i = 0;
	if (!isdigit(c) && c != '.')
			return c;
	i = 0;
	
	if (isdigit(c))
		while (isdigit(s[++i] = c = getch()))
			;
	
	if (c == '.')
		while (isdigit(s[++i] = c = getch()))
			;
	
	s[i] = '\0';
	if (c != EOF)
		ch = c;
	
	return NUMBER;
}
