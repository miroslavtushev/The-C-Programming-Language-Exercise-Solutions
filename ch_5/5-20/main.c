// Exercise 5-20. Expand dcl to handle declarations with function argument
// types, qualifiers like constm and so on.

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
    while (gettoken() != EOF)
	 {
		 strcpy(datatype, token);
		 out[0] = '\0';
		 name[0] = '\0';
		 dcl();
		 //if (tokentype != '\n')
			 //printf("syntax error\n");
		 printf("%s: %s %s\n", name, out, datatype);
	 }
    return 0;
}
