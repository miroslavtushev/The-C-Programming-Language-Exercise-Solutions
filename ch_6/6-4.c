// Exercise 6-4. Write a program that prints the distinct words in its input sorted
// into decreasing order of frequency of occurence. Precede each word by its
// count.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SIZE 1000
#define BUFSIZE 100

struct wordStr {
	char *word;
	int count;
} words[SIZE];
unsigned int curword = 0;

int getword(char *word, int lim);
int getch(void);
void _ungetch(int c);
char buf[BUFSIZE];

void _qsort(struct wordStr v[], int left, int right);
void printwords(struct wordStr words[], int curword);

int bufp = 0;
unsigned int linenum = 1;

int main()
{
	char word[BUFSIZE];
	
	while (getword(word, BUFSIZE) != EOF)
	{
		if (isalpha(word[0]))
		{
			// find the word in the array
			int i = 0;
			for (; i < curword; i++)
				if (strcmp(words[i].word, word) == 0)
				{
					words[i].count++;
					break;
				}
			if (i >= curword)
			{
				words[curword].word = malloc(strlen(word) + 1);
				strcpy(words[curword].word, word);
				words[curword++].count = 1;
			}
		}
	}
	_qsort(words, 0, curword-1);
	printwords(words, curword);
	return 0;
}

void _qsort(struct wordStr v[], int left, int right)
{
	int i, last;
	void swap(struct wordStr v[], int i, int j);
	
	if (left >= right)
		return;
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++)
		if (v[i].count > v[left].count)
			swap(v, ++last, i);
	swap(v, left, last);
	_qsort(v, left, last-1);
	_qsort(v, last+1, right);
}

void printwords(struct wordStr words[], int curword)
{
	for (int i = 0; i < curword; i++)
		printf("%4d: %s\n", words[i].count, words[i].word);
}

void swap(struct wordStr v[], int i, int j)
{
	struct wordStr temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

int getword(char *word, int lim)
{
	int c;
	char *w = word;
	
	while (isspace(c = getch()))
		if (c == '\n')
			linenum++;
	
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
