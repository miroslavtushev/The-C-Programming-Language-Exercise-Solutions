// Exercise 4-2. Extend atof to handle scientific notation of the form
//			123.45e-6
// where a floating point number may be followed by e or E and an optionally
// signed exponent.

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

double _atof(char s[]);

int main()
{
	printf("%f\n", _atof("123.45e-6"));
	return 0;
}

double _atof(char s[])
{
	double val, power;
	int i, sign;
	
	for (i = 0; isspace(s[i]); i++) // skipping whitespaces
		;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if (s[i] == '.')
		i++;
	for (power = 1.0; isdigit(s[i]); i++)
	{
		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;
	}
	// check for scientific notation
	if (tolower(s[i]) == 'e' && s[++i] != '\0')
	{
		int ssign = (s[i] == '-') ? -1 : 1;
		char exp[3];
		int j = 0;
		while ((exp[j++] = s[++i]) != '\0')
			;
		int p = atoi(exp);
		if (ssign)
			while (p-- > 0)
				power *= 10.0;
		else
			while (p-- > 0)
				power /= 10.0;
	}
	return sign * val / power;
}
