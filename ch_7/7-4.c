// Exercise 7-4. Write a private version of scanf analogous to minprintf from
// the previous section.

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>
#include <string.h>

int minscanf(char *format, ...);
unsigned oct_to_dec(int in);
int hex_to_dec(char *hexVal);

int main()
{
	int day, year;
	char monthname[20];
	
	minscanf("%d %s %d", &day, monthname, &year);
	printf("%d %s %d\n", day, monthname, year);
	return 0;
}

int minscanf(char *format, ...)
{
	// reading input
	char input[1000];
	int c, i;
	i = 0;
	while ((c = getchar()) != EOF)
		input[i++] = c;
	input[i] = '\0';
	
	va_list ap;
	char *pfrmt;
	char *pinpt = input;
	char *tok;
	
	va_start(ap, format);
	for (pfrmt = format; *pfrmt; pfrmt++)
	{
		if (*pfrmt != '%')
			continue;

		switch (*++pfrmt)
		{
			case 'd':
			case 'i':
				tok = strsep(&pinpt, " \t\n");
				if (*tok == '0' && tolower(*(tok+1)) != 'x')
				{
					tok++;
					unsigned oct = oct_to_dec(atoi(tok));
					*va_arg(ap, unsigned*) = oct;
					break;
				}
				else if (*tok == '0' && tolower(*(tok+1)) == 'x')
				{
					tok += 2;
					int hex = hex_to_dec(tok);
					*va_arg(ap, int*) = hex;
					break;
				}
				else
				{
					*va_arg(ap, int*) = atoi(tok);
					break;
				}
			case 'o':
				tok = strsep(&pinpt, " \t\n");
				while (*tok == '0')
					tok++;
				unsigned oct = oct_to_dec(atoi(tok));
				*va_arg(ap, unsigned*) = oct;
				break;
			case 'x':
				tok = strsep(&pinpt, " \t\n");
				if (*tok == '0' && tolower(*(tok+1)) == 'x')
					tok += 2;
				int hex = hex_to_dec(tok);
				*va_arg(ap, int*) = hex;
				break;
			case 'u':
				tok = strsep(&pinpt, " \t\n");
				*va_arg(ap, unsigned*) = atoi(tok);
				break;
			case 'f':
				tok = strsep(&pinpt, " \t\n");
				*va_arg(ap, float*) = atof(tok);
				break;
			case 's':
				tok = strsep(&pinpt, " \t\n");
				strcpy(va_arg(ap, char*), tok);
				break;
			default:
				break;
		}
	}
	va_end(ap);
	return 0;
}

unsigned oct_to_dec(int in)
{
	int dec_value = 0;
	int base = 1;
	
	int temp = in;
	while (temp)
	{
		dec_value += (temp % 10) * base;
		temp = temp / 10;
		base = base * 8;
	}
	return dec_value;
}

int hex_to_dec(char *hexVal)
{
	int len = strlen(hexVal);
	int base = 1;
	int dec_val = 0;
	
	for (int i=len-1; i>=0; i--)
	{
		if (hexVal[i]>='0' && hexVal[i]<='9')
		{
			dec_val += (hexVal[i] - 48)*base;
			
			base = base * 16;
		}
		else if (hexVal[i]>='A' && hexVal[i]<='F')
		{
			dec_val += (hexVal[i] - 55)*base;
			
			base = base*16;
		}
	}
	
	return dec_val;
}
