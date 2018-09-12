//compile: ex_8-7.c
//run: ./a.out

/*Exercise 8-7: malloc accepts a size request without checking its plausibility;
free believes that the block it is asked to free contains a valid size field.
Improve these routines so they take more pains with error checking.*/

//Note: static variable keeps track of remaining bytes from initial possible amount, defined as 100000, reducing it as malloc is called
//free will therefore never get an invalid size field, as if it is too large, it will never be asked for in the first place.

#include <stdio.h>
#define NALLOC 1024
#define MAXBYTES 100000

typedef long double Align; //my machine
union header {
	struct {
		union header *ptr;
		unsigned size;
	} s;
	Align x;
};

typedef union header Header;
int free_(void *);
void *m_alloc(unsigned);
static Header base;
static Header *freep = NULL;
static Header *more_core(unsigned);

static int rem_bytes = MAXBYTES;

int main(){
	char *buf;
	int i;
	buf = (char *) m_alloc(1000001);
	if(buf == NULL)
		printf("error checking working");
}

void *m_alloc(unsigned nbytes){
	Header *p, *prevp;

	unsigned nunits;

	nunits = (nbytes+sizeof(Header) - 1)/sizeof(Header) + 1;

	//NALLOC is what more_core will eventually ask for, so it must be anticipated
	rem_bytes -= nunits < NALLOC ? NALLOC*sizeof(Header) : nunits*sizeof(Header);
	if(rem_bytes < 0){
		rem_bytes += nunits < NALLOC ? NALLOC*sizeof(Header) :  nunits*sizeof(Header);
		return NULL;
	}
	else if(nbytes == 0){
		return NULL;
	}
	
	if((prevp = freep) == NULL) {
		base.s.ptr = freep = prevp = &base;
		base.s.size = 0;
	}

	for(p = prevp->s.ptr; ; prevp = p, p = p->s.ptr){
		if(p->s.size >= nunits){
			if(p->s.size == nunits)
				prevp->s.ptr = p->s.ptr;
			else {
				p->s.size -= nunits;
				p += p->s.size;
				p->s.size = nunits;
			}
			freep = prevp;
			return (void *)(p + 1);
		}
		if(p == freep){
			if((p = more_core(nunits)) == NULL){
				rem_bytes += nunits < NALLOC ? NALLOC*sizeof(Header) :  nunits*sizeof(Header);
				return NULL;
			}
		}
	}
}

static Header *more_core(unsigned nu){
	char *cp, *sbrk(int);
	Header *up;

	if(nu < NALLOC)
		nu = NALLOC;

	cp = sbrk(nu * sizeof(Header));
	if(cp == (char *) - 1)
		return NULL;
	up = (Header *) cp;
	up->s.size = nu;
	free_((void *)(up + 1));
	return freep;
}

int free_(void *ap){
	Header *bp, *p;
	
	bp = (Header *)ap -1;
	for(p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr){
		if(p >= p->s.ptr && (bp > p || bp < p->s.ptr))
			break;
	}
	if(bp + bp->s.size == p->s.ptr) {
		bp->s.size += p->s.ptr->s.size;
		bp->s.ptr = p->s.ptr->s.ptr;
	} else
		bp->s.ptr = p->s.ptr;
	if(p + p->s.size == bp){
		p->s.size += bp->s.size;
		p->s.ptr = bp->s.ptr;
	} else
		p->s.ptr = bp;

	freep = p;
}
