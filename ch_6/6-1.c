// Exercise 6-1. Our version of getword does not properly handle underscores,
// stirng constants, comments, or preprocessor control lines. Write a better
// version.

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100
#define BUFSIZE 100
#define NKEYS (sizeof keytab / sizeof keytab[0])

enum { FALSE, TRUE };

struct key
{
	char *word;
	int count;
} keytab[] =
{
	"auto", 0,
	"break",0,
	"case",0,
	"char",0,
	"continue",0,
	"do",0,
	"default",0,
	"const",0,
	"double",0,
	"else",0,
	"enum",0,
	"extern",0,
	"for",0,
	"if",0,
	"goto",0,
	"float",0,
	"int",0,
	"long",0,
	"register",0,
	"return",0,
	"signed",0,
	"static",0,
	"sizeof",0,
	"short",0,
	"struct",0,
	"switch",0,
	"typedef",0,
	"union",0,
	"unsigned",0,
	"void",0,
	"volatile",0,
	"while",0
};

int getword(char *, int);
int binsearch(char *, struct key *, int);
int getch(void);
void _ungetch(int);

char buf[BUFSIZE];
int bufp = 0;

int ignore_string = FALSE;
int ignore_comment = FALSE;
int ignore_prep = FALSE;

int main()
{
	int n;
	char word[MAXWORD];
	
	while (getword(word, MAXWORD) != EOF)
	{
		if (!ignore_string && !ignore_comment && !ignore_prep)
		{
			if (!(strcmp(word, "\"")))
			{
				ignore_string = TRUE;
				continue;
			}
			else if (!(strcmp(word, "/*")))
			{
				ignore_comment = TRUE;
				continue;
			}
			else if (!(strcmp(word, "#")))
			{
				ignore_prep = TRUE;
				continue;
			}
			if (isalpha(word[0]))
				if ((n = binsearch(word, keytab, NKEYS)) >= 0)
					keytab[n].count++;
		}
		else
		{
			if (!(strcmp(word, "\"")) && !ignore_comment && !ignore_prep)
				ignore_string = FALSE;
			else if (!(strcmp(word, "*/")) && !ignore_string && !ignore_prep)
				ignore_comment = FALSE;
		}
	}
	
	for (n = 0; n < NKEYS; n++)
		if (keytab[n].count > 0)
			printf("%4d %s\n", keytab[n].count, keytab[n].word);
	return 0;
}

int binsearch(char *word, struct key tab[], int n)
{
	int cond;
	int low, high, mid;
	
	low = 0;
	high = n - 1;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if ((cond = strcmp(word, tab[mid].word)) < 0)
			high = mid - 1;
		else if (cond > 0)
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}

int getword(char *word, int lim)
{
	int c;
	char *w = word;
	
	while (isspace(c = getch()))
		if (c == '\n')
			ignore_prep = FALSE;
	
	if (c != EOF)
		*w++ = c;
	if (!isalpha(c))
	{
		*w = '\0';
		return c;
	}
	for (; --lim > 0; w++)
		if (!isalnum(*w = getch()) && *w != '_')
		{
			_ungetch(*w);
			break;
		}
	*w = '\0';
	return word[0];
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
