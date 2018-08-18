//compile: gcc ex_2-6.c
//run: ./a.out

//Exercise 2-6: Write a function setbits(x,p,n,y) that returns x with the n bits that begin at position p set to the rightmost n bits of y, leaving the other bits unchanged.

#include <stdio.h>

void print_binary(unsigned int d){
	int tmp;
	if(d > 0){
		tmp = d;
		d = d >> 1;
		d = d << 1;
		if(d < tmp){
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
	
	//obtain right cut of y and right cuts of x
	y_cut = (~(~0 << n) & y) << p;
	print_binary(y_cut);
	printf("\n");
	x_cut = ~(~0 << p) & x;
	print_binary(x_cut);
	printf("\n");
	//obtain left cut of x for final or
	x = x >> n;
	x = x  << (n + p);
	return (x | y_cut | x_right_cut);

	

}

int main(){
	print_binary(setbits(0b1100101011010, 4, 3, 0b10101101001010));
}
