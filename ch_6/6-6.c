// Exercise 6-6. Implement a simple version of the #define processor (i.e., no
// arguments) suitable for use with C programs, based on the routines of this
// section. You may also find getch and ungetch helpful.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASHSIZE 101
#define BUFSIZE 10
#define MAXWORD 100

struct nlist {
	struct nlist *next;
	char *name;
	char *defn;
};

unsigned hash(char *s);
struct nlist *lookup(char *s);
struct nlist *lookupprev(char *s);
struct nlist *install(char *name, char *defn);
void undef(char *name, char *defn);
int getword(char *word, int lim);
int getch(void);
void _ungetch(int c);

char buf[BUFSIZE];
int bufp = 0;

static char program[10000];

static struct nlist *hashtab[HASHSIZE];

int main()
{
	char word[MAXWORD];
	char name[MAXWORD];
	char defn[MAXWORD];
	
	while (getword(word, MAXWORD) != EOF)
	{
		struct nlist *np;
		
		if (strcmp(word, "#define") == 0)
		{
			getword(name, MAXWORD);
			getword(defn, MAXWORD);
			install(name, defn);
			
			strcat(program, "#define ");
			strcat(program, name);
			strcat(program, " ");
			strcat(program, defn);
		}
		else if ((np = lookup(word)) != NULL)
		{
			strcat(program, np->defn);
		}
		else
		{
			strcat(program, word);
		}
	}
	printf("%s", program);
	return 0;
}

unsigned hash(char *s)
{
	unsigned hashval;
	
	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}

struct nlist *lookup(char *s)
{
	struct nlist *np;
	
	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return np;
	return NULL;
}

struct nlist *lookupprev(char *s) // looks up 1 elem. BEFORE the s
{
	struct nlist *np;
	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (np->next != NULL && strcmp(s, np->next->name) == 0)
			return np;
	return NULL;
}

struct nlist *install(char *name, char *defn)
{
	struct nlist *np;
	unsigned hashval;
	
	if ((np = lookup(name)) == NULL)
	{
		np = (struct nlist *) malloc(sizeof(*np));
		if (np == NULL || (np->name = strdup(name)) == NULL)
			return NULL;
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	}
	else
		free((void *) np->defn);
	if ((np->defn = strdup(defn)) == NULL)
		return NULL;
	return np;
}

void undef(char *name, char *defn)
{
	struct nlist *np;
	
	if ((np = lookupprev(name)) != NULL)
	{
		struct nlist *l = np->next;
		if (np->next->next != NULL)
		{
			np->next = np->next->next;
		}
		free((void *) l->defn);
		free((void *) l->name);
		free((void *) l);
		l = NULL;
	}
	else if ((np = lookup(name)) != NULL)
	{
		if (np->next != NULL)
		{
			struct nlist *l = np->next;
			unsigned hashval = hash(l->name);
			hashtab[hashval] = l;//
		}
		free((void *) np->defn);
		free((void *) np->name);
		free((void *) np);
		np = NULL;
	}
}

int getword(char *word, int lim)
{
	int c;
	char *w = word;
	
	while (isspace(c = getch()))
	{
		char s[2];
		s[0] = c;
		s[1] = '\0';
		strcat(program, s);
	}

	if (c != EOF)
		*w++ = c;
	if (!isalpha(c) && c != '#' && !isnumber(c))
	{
		*w = '\0';
		return c;
	}
	for (; --lim > 0; w++)
		if (!isalnum(*w = getch()) && *w != '_' && *w != '#')
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
