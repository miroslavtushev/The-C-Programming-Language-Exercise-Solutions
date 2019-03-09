#define NUMBER '0'
#define TOP '^'
#define DUPLICATE '>'
#define SWAP '<'
#define CLEAR ';'
#define SIN '}'
#define EXP '{'
#define POW '"'
#define RECENT '?'

int getch(void);
void _ungetch(int);
int getop(char[]);
void push(double);
double pop(void);
