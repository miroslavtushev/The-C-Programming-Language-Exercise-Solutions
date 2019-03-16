// Exercise 5-5. Write versions of the library functions strncpy, strncat, and
// strncmp, which operate on at most the first n characters of their argument
// strings. For example, strncpy(s,t,n) copies at most n characters of t to s.

#include <stdio.h>
#define MAXSIZE 100

char *_strncpy(char*, char*, int);
char *_strncat(char*, char*, int);
int _strncmp(char*, char*, int);

int main()
{
	char a1[MAXSIZE] = "aabb";
	char b1[MAXSIZE] = "String2";
	char *c = _strncpy(b1, a1, 5);
	
	char a2[MAXSIZE] = "aabb";
	char b2[MAXSIZE] = "String2";
	char *d = _strncat(b2, a2, 4);
	
	char a3[MAXSIZE] = "A really long string";
	char b3[MAXSIZE] = "A really short string";
	int res = _strncmp(a3, b3, 8);
	
	return 0;
}

char *_strncpy(char *s, char *ct, int n)
{
	int i = strlen(ct);
	int j;
	for (j = 0; j < i && j < n; j++)
		s[j] = ct[j];
	s[j++] = '\0';
	for (; j <= n; s[j++] = '\0')
		;
	return s;
}

char *_strncat(char *s, char *ct, int n)
{
	int i = strlen(s);
	int j = 0;
	
	while (j < n && (s[i++] = ct[j++]))
		;
	s[i++] = '\0';
	return s;
}

int _strncmp(char *cs, char *ct, int n)
{
	int i;
	for (i = 0; i < n && cs[i] == ct[i]; i++)
		;
	return cs[i] - ct[i];
}

