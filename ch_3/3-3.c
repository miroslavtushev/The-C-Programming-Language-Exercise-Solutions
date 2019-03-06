// Exercise 3-3. Write a function expand(s1, s2) that expands shorthand notations like
// a-z in the string s1 into equivalent complete list abc...xyz in s2. Allow for letters of either
// case and digits, and be prepared to handle cases like a-b-c and a-z0-9 and -a-z.
// Arrange that a leading or trailing - is taking literally.

#include <stdio.h>
#include <ctype.h>
#define SIZE 100
#define STEP 3

void expand(char s1[], char s2[]);

int main()
{
	char s1[SIZE] = "-0-9h-zH-L-";
	char s2[SIZE];
	expand(s1, s2);
	printf("%s\n", s2);
	return 0;
}

void expand(char s1[], char s2[])
{
	if (strlen(s1) < 3)
		return;
	
	int i = 0; // for input string
	int j = 0; // for output string

	for (; i < strlen(s1); i+=STEP)
	{
		// skiping -
		for (; !isalnum(s1[i]) && i < strlen(s1); i++)
			;
		
		char start = s1[i];
		// checking for correct input format
		if (s1[i+1] != '-')
			return;
		if (!isalnum(s1[i+2]))
			return;
		char end = s1[i+2];
		
		// more checks
		if (end < start || (isalpha(end) && isdigit(start)) || (isdigit(end) && isalpha(start)))
			return;
		
		while (start != end)
		{
			s2[j++] = start++;
		}
		s2[j++] = end;
	}
	s2[j] = '\0';
}
