//compile: ex_8-8.c
//run: ./a.out

/*Exercise 8-8: Write a routine bfree(p,n) that will free an arbitrary block p
of n characters into the free list maintained by malloc and free. By using bfree,
a user can add a static or external array to the free list at any time.*/

//last exercise - what a great book!

#include <stdio.h>
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
void *b_free(char *, unsigned);
void *m_alloc(unsigned);
static Header base;
static Header *freep = NULL;
static Header *more_core(unsigned);

static Header muh_header;

int main(){
	m_alloc(1);
	b_free((char *)&muh_header, sizeof(Header));
	Header *p;
	for(p = base.s.ptr; p != &base && p != &muh_header; p = p->s.ptr)	
		;
	printf("%p | %p\n", (void*)p, (void*)&muh_header);

}

void *b_free(char *p, unsigned n){

	//p
	if(sizeof(char)*n < sizeof(Header)){ 
		return NULL;
	}
	
	Header *q = (Header *) p;
	q->s.size = n/sizeof(Header); //if it is 100 bytes, then the size including the header will have to cut some out (4), and set the size to 5
	free_((void*)(q+1));
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
