#include <stdio.h>
#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;
extern int ch;

int getch(void)
{
	if (ch > 0)
	{
		int c = ch;
		ch = 0;
		return c;
	}
	else
		return getchar();
}

void _ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}
