//program example from 8.7; 
#include <stdio.h>
#include <stdlib.h>
#define NALLOC 1024

typedef long double Align; //my machine
union header {
	struct {
		union header *ptr;
		unsigned size;
	} s;
	Align x;
};

typedef union header Header;
void free_(void *);
void *m_alloc(unsigned);
static Header base;
static Header *freep = NULL;
static Header *more_core(unsigned);

int main(){
	char *buf;
	int i;
	buf = (char *) m_alloc(10 + 1);
	for(i = 0; i < 10; i++)
		*buf++ = 'a';
	*buf = '\0';
	buf = buf - i;
	printf("%s", buf);
}

void *m_alloc(unsigned nbytes){
	Header *p, *prevp;
	unsigned nunits;

	nunits = (nbytes+sizeof(Header) - 1)/sizeof(Header) + 1;
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
			if((p = more_core(nunits)) == NULL)
				return NULL;
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

void free_(void *ap){
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
