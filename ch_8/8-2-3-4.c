// Exercise 8-2. Rewrite fopen and _fillbuf with fields instead of explicit bit
// operations. Compare code size and execution speed.

// Exercise 8-3. Design and write _flushbuf, fflush, and fclose.

// Exercise 8-4. The standard library function
//		int fseek(FILE *fp, long offset, int origin)
// is identical to lseek....
// ...Write fseek.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#define PERMS 0666

// implementation-specific
#define _READ 			__SRD
#define _WRITE 		__SWR
#define _UNBUF			__SNBF
#define _EOF			__SEOF
#define _ERR			__SERR
#define OPEN_MAX 		FOPEN_MAX
#define getc(p) 		(--(p)->_r >= 0 ? (unsigned char) *(p)->_p++ : _fillbuf_bits(p))
#define getc_fields(p, f) 		(--(p)->_r >= 0 ? (unsigned char) *(p)->_p++ : _fillbuf_fields(p, f))
#define putc(x,p)		(--(p)->_w >= 0 ? *(p)->_p++ = (x) : _flushbuf_bits((x),p))
FILE _iob[OPEN_MAX] =
{
	{ 0, 0, 0, _READ, 0 },
	{ 0, 0, 0, _WRITE, 1 },
	{ 0, 0, 0, _WRITE | _UNBUF, 2 }
};
// end
typedef struct fields{
	int read;
	int write;
	int eof;
	int err;
	int unbuf;
} Fields;

FILE *fopen_bits(char *name, char *mode);
FILE *fopen_fields(char *name, char *mode, struct fields *f);
int _fillbuf_bits(FILE *fp);
int _fillbuf_fields(FILE *fp, struct fields *f);
int _flushbuf_bits(int n, FILE *fp);
int fflush_bits(FILE *fp);
int fclose_bits(FILE *fp);
int fseek_bits(FILE *fp, long offset, int origin);

int main(int argc, char **argv)
{
	FILE *f1;
	if ((f1 = fopen_bits(*++argv, "w")) != NULL)
	{
		for (int i = 0; i < 10; i++)
			putc('c',f1);
	}
	fseek_bits(f1, 1L, 0);
	putc('d',f1);
	fclose_bits(f1);
	
	return 0;
}

FILE *fopen_bits(char *name, char *mode)
{
	int fd;
	FILE *fp;
	
	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;
	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if ((fp->_flags & (_READ | _WRITE)) == 0)
			break;
	if (fp >= _iob + OPEN_MAX)
		return NULL;
	
	if (*mode == 'w')
		fd = creat(name, PERMS);
	else if (*mode == 'a')
	{
		if ((fd = open(name, O_WRONLY, 0)) == -1)
			fd = creat(name, PERMS);
		lseek(fd, 0L, 2);
	}
	else
		fd = open(name, O_RDONLY, 0);
	if (fd == -1)
		return NULL;
	fp->_file = fd;
	fp->_r = 0;
	fp->_w = 0;
	fp->_bf._base = NULL;
	fp->_flags = (*mode == 'r') ? _READ : _WRITE;
	return fp;
}

FILE *fopen_fields(char *name, char *mode, struct fields *f)
{
	int fd;
	FILE *fp;
	
	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;
	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if ((f->read == 0 || f->write == 0))
			break;
	if (fp >= _iob + OPEN_MAX)
		return NULL;
	
	if (*mode == 'w')
		fd = creat(name, PERMS);
	else if (*mode == 'a')
	{
		if ((fd = open(name, O_WRONLY, 0)) == -1)
			fd = creat(name, PERMS);
		lseek(fd, 0L, 2);
	}
	else
		fd = open(name, O_RDONLY, 0);
	if (fd == -1)
		return NULL;
	fp->_file = fd;
	fp->_r = 0;
	fp->_w = 0;
	fp->_bf._base = NULL;
	if (*mode == 'r')
		f->read = 1;
	else
		f->write = 1;
	return fp;
}

int _fillbuf_bits(FILE *fp)
{
	int bufsize;
	
	if ((fp->_flags&(_READ | _EOF | _ERR)) != _READ)
		return EOF;
	bufsize = (fp->_flags & _UNBUF) ? 1 : BUFSIZ;
	if (fp->_bf._base == NULL)
		if ((fp->_bf._base = (char *) malloc(bufsize)) == NULL)
			return EOF;
	fp->_p = fp->_bf._base;
	fp->_r = read(fp->_file, fp->_p, bufsize);
	if (--fp->_r < 0)
	{
		if (fp->_r == -1)
			fp->_flags |= _EOF;
		else
			fp->_flags |= _ERR;
		fp->_r = 0;
		return EOF;
	}
	return (unsigned char) *fp->_p++;
}

int _fillbuf_fields(FILE *fp, struct fields *f)
{
	int bufsize;
	if (f->eof == 1 || f->err == 1)
		return EOF;
	bufsize = f->unbuf ? 1 : BUFSIZ;
	if (fp->_bf._base == NULL)
		if ((fp->_bf._base = (char *) malloc(bufsize)) == NULL)
			return EOF;
	fp->_p = fp->_bf._base;
	fp->_r = read(fp->_file, fp->_p, bufsize);
	if (--fp->_r < 0)
	{
		if (fp->_r == -1)
			f->eof = 1;
		else
			f->err = 1;
		fp->_r = 0;
		return EOF;
	}
	return (unsigned char) *fp->_p++;
}

int _flushbuf_bits(int x, FILE *fp)
{
	int bufsize = (fp->_flags & _UNBUF) ? 1 : BUFSIZ;
	
	if ((fp->_flags&(_WRITE | _EOF | _ERR)) != _WRITE)
		return EOF;
	// if function called for the first time
	if (fp->_bf._base == NULL)
	{
		bufsize = (fp->_flags & _UNBUF) ? 1 : BUFSIZ;
		if ((fp->_bf._base = (char *) malloc(bufsize)) == NULL)
			return EOF;
		else
		{
			fp->_p = fp->_bf._base;
			fp->_w = bufsize;
			*fp->_p = x;
		}
	}
	else 		// if buf is full
	{
		write(fp->_file, fp->_bf._base, bufsize);
		free(fp->_bf._base);
		fp->_bf._base = NULL;
		fp->_p = 0;
		fp->_w = 0;
	}
//	if (--fp->_w < 0)
//	{
//		if (fp->_w == -1)
//			fp->_flags |= _EOF;
//		else
//			fp->_flags |= _ERR;
//		fp->_w = 0;
//		return EOF;
//	}
	return (unsigned char) *fp->_p++;
}

int fflush_bits(FILE *fp)
{
	int bufsize = (fp->_flags & _UNBUF) ? 1 : BUFSIZ;

	if ((fp->_flags&(_WRITE | _EOF | _ERR)) != _WRITE)
		return EOF;
	if (fp->_bf._base != NULL)
	{
		write(fp->_file, fp->_bf._base, bufsize - fp->_w+1);
		free(fp->_bf._base);
		fp->_bf._base = NULL;
		fp->_p = 0;
		fp->_w = 0;
		fp->_r = 0;
	}
	else
	{
		fp->_flags&_ERR;
		return 1;
	}
	return 0;
}

int fclose_bits(FILE *fp)
{
	fflush_bits(fp);
	// destroy the file?
	free(fp->_bf._base);
	free(fp->_p);
	//free(fp);
	return 0;
}

int fseek_bits(FILE *fp, long offset, int origin)
{
	if (fp == NULL)
		return -1L;
	if (fp->_flags & _WRITE)
		fflush_bits(fp);
	return lseek(fp->_file, offset, origin);
}
