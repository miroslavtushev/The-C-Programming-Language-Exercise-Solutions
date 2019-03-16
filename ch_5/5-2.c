// Exercise 5-2. Write getfloat, the floating-point analog of getint. What
// type does getfloat return as its function value?

#include <ctype.h>
#include <stdio.h>
#define BUFSIZE 100
#define SIZE 10

char buf[BUFSIZE];
int bufp = 0;

int getfloat(float *pn);
int getch(void);
void _ungetch(int);

int main()
{
	int n;
	float array[SIZE];
	for (n = 0; n < SIZE && getfloat(&array[n]) != EOF; n++)
		;
	return 0;
}

int getfloat(float *pn)
{
	float power;
	int c, sign;
	
	while (isspace(c = getch()))
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-')
	{
		_ungetch(c);
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-')
		c = getch();
	for (*pn = 0.0; isdigit(c); c = getch())
		*pn = 10.0 * *pn + (c - '0');
	if (c == '.')
		c = getch();
	for (power = 1.0; isdigit(c); c = getch())
	{
		*pn = 10.0 * *pn + (c - '0');
		power *= 10.0;
	}
	*pn = *pn * sign / power;

	if (c != EOF)
		_ungetch(c);
	return *pn;
}

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void _ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}
