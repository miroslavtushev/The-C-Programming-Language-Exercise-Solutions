// Exercise 4-14. Define a macro swap(t,x,y) that interchanges two arguments
// of type t. (Block structure will help.)

#include <stdio.h>

#define swap(t, x, y) {t z = x; x = y; y = z;}

int main()
{
	int i = 5;
	int j = 6;
	swap(int, i, j);
	return 0;
}
