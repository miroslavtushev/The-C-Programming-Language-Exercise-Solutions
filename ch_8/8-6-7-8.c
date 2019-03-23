// Exercise 8-6. The standard library functions calloc(n, size) returns a
// pointer to n objects of size size, with the storage initialized to zero. Write
// calloc, by calling malloc or by modifying it.

// Exercise 8-7. malloc accepts a size request without checking its plausability;
// free believes that the block it is asked to free contains a valid size field.
// Improve these routines so they takemore pains with error checking.

// Exercise 8-8. Write a routine bfree(p,n) that will free an arbitrary block p
// of n characters into the free list maintained by malloc and free. By using
// bfree, a user can add a static or external array to the free list at any time.

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#define NALLOC 1024

typedef long Align;
union header {
	struct {
		union header *ptr;
		unsigned size;
	} s;
	Align x;
};
typedef union header Header;

static Header base;
static Header *freep = NULL;

void _free(void *ap);
void *_malloc(unsigned nbytes);
void *_calloc(unsigned n, unsigned size);
static Header *morecore(unsigned nu);
void _bfree(void *p, int n);

int main()
{
	char *c1 = _malloc(20*sizeof(char));
	_free(c1);
	
	double c2[100];
	_bfree(&c2, 100*sizeof(double));

	int *i1 = _malloc(1000*sizeof(int));
	_free(i1);

	double *d1 = _malloc(30*sizeof(double));
	_free(d1);
	
	c1[4] = 't';
	i1[31] = 5;
	d1[50] = 0.1;
	
	return 0;
}

void *_malloc(unsigned nbytes)
{
	Header *p, *prevp;
	unsigned nunits;
	
	nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
	if (nunits > NALLOC)
		return;
	if ((prevp = freep) == NULL)
	{
		base.s.ptr = freep = prevp = &base;
		base.s.size = 0;
	}
	for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr)
	{
		if (p->s.size >= nunits)
		{
			if (p->s.size == nunits)
				prevp->s.ptr = p->s.ptr;
			else
			{
				p->s.size -= nunits;
				p += p->s.size;
				p->s.size = nunits;
			}
			freep = prevp;
			return (void*)(p+1);
		}
		if (p == freep)
			if ((p = morecore(nunits)) == NULL)
				return NULL;
	}
}

void *_calloc(unsigned n, unsigned size)
{
	void *p = _malloc(n*size);
	memset(p, 0, n*size);
	return p;
}

static Header *morecore(unsigned nu)
{
	char *cp;
	Header *up;
	
	if (nu < NALLOC)
		nu = NALLOC;
	cp = sbrk(nu * sizeof(Header));
	if (cp == (char *) - 1)
		return NULL;
	up = (Header *) cp;
	up->s.size = nu;
	_free((void *) (up + 1));
	return freep;
}

void _free(void *ap)
{
	if (ap == NULL)
		return;
	Header *bp, *p;
	
	bp = (Header *)ap - 1;
	if (bp->s.size < 1)
		return;
	for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
		if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
			break;
	
	if (bp + bp->s.size == p->s.ptr)
	{
		bp->s.size += p->s.ptr->s.size;
		bp->s.ptr = p->s.ptr->s.ptr;
	}
	else
		bp->s.ptr = p->s.ptr;
	if (p + p->s.size == bp)
	{
		p->s.size += bp->s.size;
		p->s.ptr = bp->s.ptr;
	}
	else
		p->s.ptr = bp;
	freep = p;
}

void _bfree(void *p, int n)
{
	Header *bp = p;
	if (n < sizeof(Header)) // if p doesn't occupy whole block
	{
		//???
		return;
	}
	bp->s.size = n / sizeof(Header);
	_free(bp+1);
}
