// Exercise 4-10. An alternate organization uses getline to read an entire input
// line; this makes getch and ungetch unnecessary. Revise the calculator to use
// this approach.

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

int pos = 0;

int getop(char[], char[]);
void push(double);
double pop(void);

void printtop(void);
void duplicatetop(void);
void swaptop(void);
void clearstack(void);
void printrecent(void);
void ungets(char s[]);

int _getline(char s[], int lim);

int main()
{
	int type;
	double op2;
	char s[MAXOP];
	char t[MAXOP];
	
	while (1)
	{
		int lim = _getline(s, MAXOP);
		pos = 0;
		while (pos < lim)
		{
			type = getop(s, t);
			switch (type)
			{
				case NUMBER:
					push(atof(t));
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
					break;
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
	}
	
	return 0;
}

// saves the numbers for conversion in t[]
int getop(char s[], char t[])
{
	int j = 0;
	int c;
	
	while ((c = s[pos]) == ' ' || c == '\t') // skipping whitespaces
		pos++;

	//pos--;
	t[j] = '\0';
	
	if (!isdigit(c) && c != '.')
	{
		if (c == '+' || c == '*' || c == '/' || c == '%')
		{
			pos++;
			return c;
		}
		else if (c == '-')
		{
			t[j] = c;
			if (isdigit(c = s[++pos]))
				t[++j] = c;
			else
			{
				return '-';
			}
		}
		else if (isalpha(c))
		{
			// read the text
			t[j] = c;
			while (isalpha(c = s[++pos]))
				t[++j] = c;
			if (j == 0) // variable
				return t[j];
			t[++j] = '\0';
			
			// handling text commands
			// certain commains getch "back" to remove
			// \n from the stack to prevent pop()
			if (!strcmp(t, "sin"))
				return SIN;
			else if (!strcmp(t, "exp"))
				return EXP;
			else if (!strcmp(t, "pow"))
				return POW;
			else if (!strcmp(t, "recent"))
			{
				return RECENT;
			}
			else if (!strcmp(t, "top"))
			{
				return TOP;
			}
			else if (!strcmp(t, "swap"))
			{
				return SWAP;
			}
			else if (!strcmp(t, "duplicate"))
			{
				return DUPLICATE;
			}
			else if (!strcmp(t, "clear"))
			{
				return CLEAR;
			}
			else
			{
				pos++;
				return c;
			}
		}
		else
		{
			pos++;
			return c;
		}
	}
	
	if (isdigit(c))
		while (isdigit(t[j++] = c = s[pos++]))
			;
	if (c == '.')
		while (isdigit(t[j++] = c = s[pos++]))
			;
	t[++j] = '\0';
	
	
	//if (c != EOF)
		//_ungetch(c);
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

int _getline(char s[], int lim)
{
	int c, i;
	i = 0;
	
	for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
		s[i] = c;
	if (c == '\n')
	{
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

