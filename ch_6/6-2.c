// Exercise 6-2. Write a program that reads a C program and prints in alphabetical
// order each group of variable names that are identical in the first 6 characters
// but different somewhere thereafter. Don't count words within strings and comments.
// Make 6 a parameter tha can be set from the command line.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXWORD 100
#define BUFSIZE 100

int N = 6;

enum { FALSE, TRUE };
int ignore_string = FALSE;
int ignore_comment = FALSE;

struct tgroup {
	int numofwords;
	char *word;
	char **arr;
	struct tgroup *left;
	struct tgroup *right;
};

int getword(char *word, int lim);
int getch(void);
void _ungetch(int c);
char buf[BUFSIZE];
int bufp = 0;

struct tgroup *addtree(struct tgroup *p, char *w);
void treeprint(struct tgroup *p);

int main(int argc, char **argv)
{
	if (argc > 2)
	{
		printf("Incorrect number of arguments was provided\n");
		return 1;
	}
	if (argc > 1)
	{
		N = atoi(argv[argc-1]);
		if (N <= 0)
		{
			printf("Incorrect argument was provided\n");
			return 1;
		}
	}
	
	struct tgroup *root = NULL;
	char word[MAXWORD];
	while (getword(word, MAXWORD) != EOF)
	{
		if (!ignore_string && !ignore_comment)
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
			if (isalpha(word[0]))
				root = addtree(root, word);
		}
		else
		{
			if (!(strcmp(word, "\"")) && !ignore_comment)
				ignore_string = FALSE;
			else if (!(strcmp(word, "*/")) && !ignore_string)
				ignore_comment = FALSE;
		}
	}
	
	treeprint(root);
	
	return 0;
}

struct tgroup *addtree(struct tgroup *p, char *w)
{
	int cond;

	if (p == NULL)
	{
		p = malloc(sizeof(struct tgroup));
		
		p->word = malloc(N + 1);
		strncpy(p->word, w, N);
		p->word[N+1] = '\0';
		
		p->arr = malloc(100); // enough?
		p->arr[0] = malloc(strlen(w) + 1);
		strcpy(p->arr[0], w);
		
		p->left = NULL;
		p->right = NULL;
		p->numofwords = 1;
	}
	else if ((cond = strncmp(w, p->word, N)) == 0)
	{
		p->arr[p->numofwords] = malloc(strlen(w) + 1);
		strcpy(p->arr[p->numofwords], w);
		p->numofwords++;
	}
	else if (cond < 0)
		p->left = addtree(p->left, w);
	else
		p->right = addtree(p->right, w);
	return p;
}

void treeprint(struct tgroup *p)
{
	if (p != NULL)
	{
		treeprint(p->left);
		printf("%s: ", p->word);
		for (int i = 0; i < p->numofwords; i++)
			printf("%s, ", p->arr[i]);
		printf("\n");
		treeprint(p->right);
	}
}

int getword(char *word, int lim)
{
	int c;
	char *w = word;
	
	while (isspace(c = getch()))
		;
	
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

