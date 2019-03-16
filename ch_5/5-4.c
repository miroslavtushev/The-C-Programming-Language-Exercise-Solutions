// Exercise 5-4. Write the function strend(s,t), which returns 1 of the string
// t occurs at the end of the string s, and zero otherwise.

#include <stdio.h>

int strend(char*, char*);

int main()
{
	char a[] = "This is one string.";
	char b[] = "one string.";
	printf("%d\n", strend(a, b));
	return 0;
}

int strend(char *s, char *t)
{
	int i = strlen(s) - 1;
	int j = strlen(t) - 1;
	for (; (&t[j] != t || &s[i] != s) && s[i] == t[j]; i--, j--)
		;
	return &t[j+1] == t ? 1 : 0;
}
