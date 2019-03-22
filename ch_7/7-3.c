// Exercise 7-3. Revise minprintf to handle more of the other facilities of
// printf.

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>

void minprintf(char *fmt, ...);

enum { NO, YES};

int in_format = NO;

int main()
{
	int d = 1000;
	char *w = "world";
	minprintf("There are %d people in the %-10s\n",d, w);
	return 0;
}

void minprintf(char *fmt, ...)
{
	va_list ap;
	char *p, *sval;
	int ival;
	unsigned uval;
	double dval;
	
	int padding = 0;
	int i = 0;
	char padbuf[10];
	
	char string[1000];
	int right_padding = NO;
	
	va_start(ap, fmt);
	for (p = fmt; *p; p++)
	{
		if (*p != '%' && in_format == NO)
		{
			putchar(*p);
			continue;
		}
		else if (*p == '%')
		{
			p++;
			in_format = YES;
		}
		switch (*p)
		{
			case '0': case '1': case '2': case '3': case '4': case '5':
			case '6': case '7': case '8': case '9':
				for (i = 0; isdigit(*p); p++, i++)
					padbuf[i] = *p;
				padbuf[i] = '\0';
				padding = atoi(padbuf);
				p--;
				break;
			case '-':
				right_padding = YES;
				break;
			case 'd':
			case 'i':
				ival = va_arg(ap, int);
				if (right_padding == YES)
					printf("%-*d", padding, ival);
				else
					printf("%*d", padding, ival);
				in_format = NO;
				break;
			case 'f':
				dval = va_arg(ap, double);
				if (right_padding == YES)
					printf("%-*f", padding, dval);
				else
					printf("%*f", padding, dval);
				in_format = NO;
				break;
			case 's':
				for (i = 0, sval = va_arg(ap, char*); *sval; i++, sval++)
					string[i] = *sval;
				string[i] = '\0';
				if (right_padding == YES)
					printf("%-*s", padding, string);
				else
					printf("%*s", padding, string);
				in_format = NO;
				break;
			case 'u':
				uval = va_arg(ap, unsigned);
				if (right_padding == YES)
					printf("%-*u", padding, uval);
				else
					printf("%*u", padding, uval);
				in_format = NO;
				break;
			case 'o':
				ival = va_arg(ap, int);
				if (right_padding == YES)
					printf("%-*o", padding, ival);
				else
					printf("%*o", padding, ival);
				in_format = NO;
				break;
			case 'x':
			case 'X':
				ival = va_arg(ap, int);
				if (right_padding == YES)
					printf("%-*x", padding, ival);
				else
					printf("%*x", padding, ival);
				in_format = NO;
				break;
			default:
				putchar(*p);
				break;
		}
	}
	va_end(ap);
}
