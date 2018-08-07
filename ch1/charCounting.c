//1.5.2 Example program; Count the number of characters in input

#include <stdio.h>

int main(){
	long nc;
	nc = 0;
	while(getchar() != EOF)
		++nc;
	printf("%ld\n", nc);
}
