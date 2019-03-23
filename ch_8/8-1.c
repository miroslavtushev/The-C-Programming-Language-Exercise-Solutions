// Exercise 8-1. Rewrite the program cat from Chapter 7 using read, write,
// open and close instead of their standard library equivalents. Perform
// experiments to determine the relative speeds of the two versions.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#define LOW_LEVEL 0

void filecopy(FILE *ifp, FILE *ofp); // 11.9 sec
void filecopy_low_char(int ifp, int ofp); // 21 sec
void filecopy_low_buf(int ifp, int ofp); // 0.10 sec

int main(int argc, char **argv)
{
	FILE *fp;
	int fd;
	char *prog = argv[0];
	
	clock_t start, end;
	
	if (argc == 1)
		filecopy(stdin, stdout);
	else
	{
		start = clock();
		while (--argc > 0)
#if LOW_LEVEL
			if ((fd = open(*++argv, O_RDONLY, 0)) == -1)
			{
				fprintf(stderr, "%s: can't open %s\n", prog, *argv);
				exit(1);
			}
			else
			{
				filecopy_low_buf(fd, 1);
			}
#endif
#if !LOW_LEVEL
			if ((fp = fopen(*++argv, "r")) == NULL)
			{
				fprintf(stderr, "%s: can't open %s\n", prog, *argv);
				exit(1);
			}
			else
			{
				filecopy(fp, stdout);
				fclose(fp);
			}
#endif
		end = clock();
		printf( "Number of seconds: %f\n", (end-start)/(double)CLOCKS_PER_SEC );
	}
	if (ferror(stdout))
	{
		fprintf(stderr, "%s: error writing stdout\n", prog);
		exit(2);
	}
	return 0;
}

void filecopy(FILE *ifp, FILE *ofp)
{
	int c;
	
	while ((c = getc(ifp)) != EOF)
		putc(c, ofp);
}

void filecopy_low_char(int ifp, int ofp)
{
	int c, n;
	
	while ((n = read(ifp, &c, 1)) == 1)
		write(ofp, &c, 1);
}

void filecopy_low_buf(int ifp, int ofp)
{
	int n;
	char buf[BUFSIZ];
	
	while ((n = read(ifp, buf, BUFSIZ)) > 0)
		write(ofp,buf, n);
}
