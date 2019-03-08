// Exercise 4-3 - 4-9.

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAXOP 100
#define NUMBER '0'
#define MAXVAL 100
#define BUFSIZE 100
#define TOP '^'
#define DUPLICATE '>'
#define SWAP '<'
#define CLEAR ';'
#define SIN '}'
#define EXP '{'
#define POW '"'
#define RECENT '?'

int sp = 0;
double val[MAXVAL];
char buf = 0;
double vars[26];
double recent = 0;

int getch(void);
void _ungetch(int);
int getop(char[]);
void push(double);
double pop(void);

void printtop(void);
void duplicatetop(void);
void swaptop(void);
void clearstack(void);
void printrecent(void);
void ungets(char s[]);

int main()
{
	int type;
	double op2;
	char s[MAXOP];
	
	while ((type = getop(s)) != EOF)
	{
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
			case SIN:
				push(sin(pop()));
				break;
			case EXP:
				push(exp(pop()));
				break;
			case POW:
				op2 = pop();
				push(pow(pop(), op2));
				break;
			case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': case 'h':
			case 'i': case 'j': case 'k': case 'l': case 'm': case 'n': case 'o': case 'p':
			case 'q': case 'r': case 's': case 't': case 'u': case 'v': case 'w': case 'x':
			case 'y': case 'z':
				push(vars[97 - type]);
			case '=':
				recent = pop();
				printf("\t%.8g\n", recent);
				break;
			case TOP:
				printtop();
				break;
			case DUPLICATE:
				duplicatetop();
				break;
			case SWAP:
				swaptop();
				break;
			case CLEAR:
				clearstack();
				break;
			case RECENT:
				printrecent();
				break;
			default:
				//printf("error: unknown command %s\n", s);
				break;
		}
	}
	
	return 0;
}

int getop(char s[])
{
	int i,c;
	
	while ((s[0] = c = getch()) == ' ' || c == '\t') // skipping whitespaces
		;
	s[1] = '\0';
	
	i = 0;
	if (!isdigit(c) && c != '.')
	{
		if (c == '+' || c == '*' || c == '/' || c == '%')
			return c;
		else if (c == '-')
		{
			s[++i] = c;
			if (isdigit(c = getch()))
				s[++i] = c;
			else
			{
				_ungetch(c);
				return '-';
			}
		}
		else if (isalpha(c))
		{
			// read the text
			while (isalpha(c = getch()))
				s[++i] = c;
			if (i == 0) // variable
				return s[i];
			s[++i] = '\0';
			_ungetch(c);
			
			// handling text commands
			// certain commains getch "back" to remove
			// \n from the stack to prevent pop()
			if (!strcmp(s, "sin"))
				return SIN;
			else if (!strcmp(s, "exp"))
				return EXP;
			else if (!strcmp(s, "pow"))
				return POW;
			else if (!strcmp(s, "recent"))
			{
				getch();
				return RECENT;
			}
			else if (!strcmp(s, "top"))
			{
				getch();
				return TOP;
			}
			else if (!strcmp(s, "swap"))
			{
				getch();
				return SWAP;
			}
			else if (!strcmp(s, "duplicate"))
			{
				getch();
				return DUPLICATE;
			}
			else if (!strcmp(s, "clear"))
			{
				getch();
				return CLEAR;
			}
			else
				return c;
		}
		else
			return c;
	}
	
	if (isdigit(c))
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.')
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';

	
	if (c != EOF)
		_ungetch(c);
	return NUMBER;
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

int getch(void)
{
	if (buf > 0)
	{
		char c = buf;
		buf = -1;
		return c;
	}
	else
		return getchar();
}

void _ungetch(int c)
{
	buf = c;
}

void printtop(void)
{
	if (sp > 0)
		printf("%g\n", val[sp-1]);
}

void duplicatetop(void)
{
	printf("\n");
	if (sp > 0 && sp < MAXVAL)
	{
		double temp = val[sp];
		val[sp++] = temp;
	}
}

void swaptop(void)
{
	printf("\n");
	if (sp > 1)
	{
		double temp = val[sp-1];
		val[sp-1] = val[sp-2];
		val[sp-2] = temp;
	}
}

void clearstack(void)
{
	sp = 0;
	printf("\n");
}

void printrecent(void)
{
	printf("\t%.8g\n", recent);
}

void ungets(char s[])
{
	int len = strlen(s);
	for (int i = len-1; len < 0; --i)
		_ungetch(s[i]);
}
