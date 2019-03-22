// Exercise 7-5. Rewrite the postfix calculator of Chapter 4 to use scanf and/or
// sscanf to do the input and number conversion.

#include <stdio.h>
#include <stdlib.h>
#include "calc.h"
#define MAXOP 100

int main()
{
	int type;
	double op2;
	char s[MAXOP];
	char *r = NULL;
	int sz = MAXOP;
	int offset;
	
	getline(&r, &sz, stdin);
	while ((sscanf(r, "%s%n", s, &offset)) == 1)
	{
		r += offset;
		type = getop(s);
		switch (type)
		{
			case NUMBER:
				push(atof(s));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				op2 = pop();
				if (op2 != 0.0)
					push(pop() / op2);
				else
					printf("error: division by zero\n");
				break;
			case '%':
				op2 = pop();
				push((int)pop() % (int)op2);
				break;
			default:
				printf("error: unknown command %s\n", s);
				break;
		}
	}
	printf("\t%.8g\n", pop());
	return 0;
}
