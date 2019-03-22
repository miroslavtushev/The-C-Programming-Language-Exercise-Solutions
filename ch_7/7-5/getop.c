#include <stdio.h>
#include <ctype.h>
#include "calc.h"

int ch = 0;

int getop(char s[])
{
	if (!isdigit(s[0]) && s[0] != '.')
			return s[0];
	else
		return NUMBER;
}
