#ifndef headers_h
#define headers_h

char *alloc(int);
void afree(char *p);
int _getline(char *s, int lim);
int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);
void _qsort(void *v[], int left, int right, int (*comp)(void *, void *), int order, int casefold);
int numcmp(char *s1, char *s2);
int dircmp(char *s, char *t);

#endif /* headers_h */
