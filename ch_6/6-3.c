// Exercise 6-3. Write a cross-referencer that prints a list of all words in a
// document, and, for each word, a list of the line numbers on which it occurs. Remove
// noise words like "the", "and", and so on.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFSIZE 100
#define MAXWORD 100

struct wordstruct {
	char *word;
	int *linenums;
	int curline;
	struct wordstruct *next;
};

static char *stop_words[127] = {"i", "me", "my", "myself", "we", "our", "ours", "ourselves", "you", "your", "yours", "yourself", "yourselves", "he", "him", "his", "himself", "she", "her", "hers", "herself", "it", "its", "itself", "they", "them", "their", "theirs", "themselves", "what", "which", "who", "whom", "this", "that", "these", "those", "am", "is", "are", "was", "were", "be", "been", "being", "have", "has", "had", "having", "do", "does", "did", "doing", "a", "an", "the", "and", "but", "if", "or", "because", "as", "until", "while", "of", "at", "by", "for", "with", "about", "against", "between", "into", "through", "during", "before", "after", "above", "below", "to", "from", "up", "down", "in", "out", "on", "off", "over", "under", "again", "further", "then", "once", "here", "there", "when", "where", "why", "how", "all", "any", "both", "each", "few", "more", "most", "other", "some", "such", "no", "nor", "not", "only", "own", "same", "so", "than", "too", "very", "s", "t", "can", "will", "just", "don", "should", "now"};

int getword(char *word, int lim);
int getch(void);
void _ungetch(int c);
char buf[BUFSIZE];

struct wordstruct *findword(struct wordstruct *p, char *word);
struct wordstruct *addword(struct wordstruct *p, char *word);
void printwords(struct wordstruct *words);

int bufp = 0;
unsigned int linenum = 1;

int main()
{
	char word[MAXWORD];
	struct wordstruct *words = NULL;
	
	while (getword(word, MAXWORD) != EOF)
	{
		if (isalpha(word[0]))
		{
			// check if it's a stop word
			int i;
			for (i = 0; i < 127 && strcmp(word, stop_words[i]) != 0; i++)
				;
			if (i >= 127)
				words = addword(words, word);
		}
	}
	printwords(words);
	return 0;
}

struct wordstruct *addword(struct wordstruct *p, char *word)
{
	if (p == NULL) // init, word is not found
	{
		p = malloc(sizeof(struct wordstruct));
		p->word = malloc(strlen(word) + 1);
		strcpy(p->word, word);
		
		p->linenums = malloc(100);
		p->linenums[0] = linenum;
		p->curline = 1;
		
		p->next = NULL;
	}
	else if (strcmp(p->word, word) == 0)
		p->linenums[p->curline++] = linenum;
	else
		p->next = addword(p->next, word);

	return p;
}

struct wordstruct *findword(struct wordstruct *words, char *word)
{
	struct wordstruct *p = words;
	if (p != NULL)
	{
		if (strcmp(p->word, word) == 0)
			return p;
		p->next = findword(p->next, word);
	}
	return NULL;
}

void printwords(struct wordstruct *words)
{
	struct wordstruct *p = words;
	while (p != NULL)
	{
		printf("%s: ", p->word);
		for (int i = 0; i < p->curline; i++)
			printf("%d, ", p->linenums[i]);
		printf("\n");
		
		p = p->next;
	}
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

