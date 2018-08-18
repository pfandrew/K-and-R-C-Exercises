//compile: gcc ex_2-7.c
//run: ./a.out

//Exercise 2-7: Write a function invert(x,p,n) that returns x with the n bits that begin at position p inverted (i.e., 1 changed into 0 and vice versa), leaving the others unchanged.
#include <stdio.h>
void print_binary(unsigned int d){
	if(d > 0){
		if(1 & d){
			print_binary(d >> 1);
			printf("1");
			
		}
		else
		{
			print_binary(d >> 1);
			printf("0");
		}	
	}
}
int invert(int x, int p, int n){
	int r, c, l;
	r = ~(~0 << p) & x;
	c = (((x >> p) & ~(~0 << n)) ^ (~(~0 << n))) << p;
	l = (x >> (n + p)) << (n + p);
	return (r|c|l);
}


int main(){
	print_binary(invert(0b100101100110, 4, 3));
}
