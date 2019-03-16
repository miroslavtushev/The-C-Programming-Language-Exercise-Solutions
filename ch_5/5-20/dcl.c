#include <stdio.h>
#include <string.h>
#include "headers.h"

extern char out[];
extern char name[];
extern char token[];
extern char datatype[];

int savedtoken;
int er = 0;

void dcl(void)
{
	int ns = 0;
	char c;
	
	while ((c = gettoken()) == '*' || c == MODIFIER)
	{
		if (c == '*')
			ns++;
		else if (c == MODIFIER)
			strcat(out, "constant ");
	}
	dirdcl();
	while (ns-- > 0)
		strcat(out, " pointer");
}

void dirdcl(void)
{
	extern int tokentype;
	int type;

	if (tokentype == NAME)
	{
		if (name[0] == '\0')
			strcpy(name, token);
		else
			strcat(out, token);
	}
	else
	{
		printf("error: expected name or (dcl)\n");
		savedtoken = tokentype;
		er = 1;
		return;
	}
	while ((type = gettoken()) == PARENS || type == BRACKETS) // modify for functions (accept single paren)
	{
		if (type == PARENS)
			strcat(out, " function returning");
		else
		{
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
	}
	
	if (tokentype == '(')
	{
		strcat(out, " function taking ");
		dcl();
		while (tokentype == ',')
		{
			strcat(out, ", ");
			dcl();
		}
		strcat(out, " and returning");
		if (tokentype != ')')
		{
			printf("error: missing )\n");
			savedtoken = tokentype;
			er = 1;
			return;
		}
	}
}


