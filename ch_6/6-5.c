// Exercise 6-5. Write a function undef that will remove name and definition
// from the table maintained by lookup and install.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

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

static struct nlist *hashtab[HASHSIZE];

int main()
{
	install("IN", "1");
	install("OUT", "2");
	install("SUM", "3");
	install("DEF", "4");
	install("INN", "1");
	install("IF", "1");
	undef("OUT", "2");
	install("OUT", "4");
	undef("OUT", "2");
	install("OUT", "4");
	printf("%s\n", (lookup("OUT"))->defn);
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
