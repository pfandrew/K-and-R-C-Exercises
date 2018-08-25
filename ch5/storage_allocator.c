//from section 5.4; rudimentary storage allocator
#include <stdio.h>
#include <string.h>

#define ALLOCSIZE 10000
static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n)
{
	if(allocbuf + ALLOCSIZE - allocp >= n){
		allocp += n;
		return allocp - n;
	}
	else
		return 0;
}

void afree(char *p){
	if(p >= allocbuf && p < allocbuf + ALLOCSIZE)
		allocp = p;
}

int main(){
	char* p = alloc(strlen("HELLO WORLD!"));
	p = "HELLO WORLD!";
	printf("%s\n", p);
	afree(p);
}
