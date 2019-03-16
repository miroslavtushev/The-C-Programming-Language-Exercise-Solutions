#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "headers.h"

#define MAXLEN 1000

void _qsort(void *v[], int left, int right, int (*comp)(void *, void *), int order, int casefold)
{
	int i, last;
	void swap(void *v[], int i, int j);
	
	if (left >= right)
		return;
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++)
	{
		char a[MAXLEN];
		char b[MAXLEN];
		strcpy(a, (char *)v[i]);
		strcpy(b, (char *)v[left]);

		if (casefold)
		{
			for (int i = 0; a[i] = tolower(a[i]); i++)
				;
			for (int j = 0; b[j] = tolower(b[j]); j++)
				;
		}
		if (((*comp)(a, b)*order) < 0)
			swap(v, ++last, i);
	}
	swap(v, left, last);
	_qsort(v, left, last-1, comp, order, casefold);
	_qsort(v, last+1, right, comp, order, casefold);
}

void swap(void *v[], int i, int j)
{
	void *temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

int numcmp(char *s1, char *s2)
{
	double v1, v2;
	
	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

int dircmp(char *s, char *t)
{
	while (*s != '\0' || *t != '\0')
	{
		if (*s == *t)
		{
			if (*s == '\0')
				return 0;
			else
			{
				s++;
				t++;
			}
		}
		else if (!isalnum(*s) || *s == ' ')
			s++;
		else if (!isalnum(*t) || *t == ' ')
			t++;
		else
			return *s - *t;
	}
	
	return *s - *t;
}
