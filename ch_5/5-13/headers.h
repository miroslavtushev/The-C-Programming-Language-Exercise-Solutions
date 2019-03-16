#ifndef headers_h
#define headers_h

char *alloc(int);
void afree(char *p);
int _getline(char *s, int lim);
int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);

#endif /* headers_h */
