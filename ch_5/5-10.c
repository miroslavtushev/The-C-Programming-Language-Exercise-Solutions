// Exercise 5-10. Write the program expr, which evaluates a reverse Polish
// expression from the command line, where each operator or operand is a separate
// argument. For example,
//		expr 2 3 4 + *
// evaluates 2 x (3+4).

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXVAL 100
#define MAXOP 100
#define NUMBER '0'

int sp = 0;
double val[MAXVAL];

void push(double f);
double pop(void);
int getop(char s[], char t[]);

int main(int argc, char **argv)
{
	int i = 0;
   while (++i < argc)
	{
		int c;
		double op2;
		char s[MAXOP];
		c = getop(argv[i], s);
		switch (c)
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
		}
	}
	if (sp > 0)
		printf("\t%.8g\n", pop());

	return 0;
}



void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else
	{
		printf("error: stack empty\n");
		return 0.0;
	}
}

int getop(char s[], char t[])
{
	int i, c;
	t[0] = c = s[0];

	if (!isdigit(c) && c != '.')
		return c;
	i = 1;
	
	if (isdigit(c))
		while (isdigit(t[i] = s[i]))
			i++;
	
	if (c == '.')
		while (isdigit(t[i] = s[i]))
			i++;
	
	s[i] = '\0';
	
	return NUMBER;
}
