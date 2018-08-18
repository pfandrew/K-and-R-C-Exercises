//compile: gcc ex_2-6.c
//run: ./a.out

//Exercise 2-6: Write a function setbits(x,p,n,y) that returns x with the n bits that begin at position p set to the rightmost n bits of y, leaving the other bits unchanged.

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

int power(int base, int exp){
	if(exp == 0)
		return 1;
	else
		return base*power(base, --exp);
}

int setbits(int x, int p, int n, int y){
	int y_cut, x_right_cut;
	y_cut = (~(~0 << n) & y) << p;
	x_right_cut = ~(~0 << p) & x;
	x = x >> (n + p);
	x = x  << (n + p);
	return (x | y_cut | x_right_cut);

}

int main(){
	print_binary(setbits(0b1100101011010, 4, 3, 0b10101101001010));
}
