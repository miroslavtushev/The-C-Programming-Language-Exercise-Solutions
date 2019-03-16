#ifndef headers_h
#define headers_h

char *alloc(int);
void afree(char *p);
int _getline(char *s, int lim);
int readlines(char *lineptr[], int maxlines, char lines[], int size);
void writelines(char *lineptr[], int nlines);
void _qsort(char *v[], int left, int right);

#endif /* headers_h */
