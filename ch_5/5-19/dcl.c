#include <stdio.h>
#include <string.h>
#include "headers.h"

extern char out[];
extern char name[];
extern char token[];

int savedtoken;
int er = 0;

void dcl(void)
{
	int ns;
	
	for (ns = 0; gettoken() == '*'; )
		ns++;
	dirdcl();
	while (ns-- > 0)
		strcat(out, " pointer to");
}

void dirdcl(void)
{
	extern int tokentype;
	int type;
	
	if (tokentype == '(')
	{
		dcl();
		if (tokentype != ')')
		{
			printf("error: missing )\n");
			savedtoken = tokentype;
			er = 1;
			return;
		}
	}
	else if (tokentype == NAME)
		strcpy(name, token);
	else
	{
		printf("error: expected name or (dcl)\n");
		savedtoken = tokentype;
		er = 1;
		return;
	}
	while ((type = gettoken()) == PARENS || type == BRACKETS)
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
}


