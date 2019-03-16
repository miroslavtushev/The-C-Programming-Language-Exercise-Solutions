#ifndef Header_h
#define Header_h

void dcl(void);
void dirdcl(void);
int gettoken(void);
int getch(void);
void _ungetch(int c);

enum { NAME, PARENS, BRACKETS };

#endif /* Header_h */
