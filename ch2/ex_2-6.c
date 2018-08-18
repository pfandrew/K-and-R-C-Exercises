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
			return;
			
		}
		else
		{
			print_binary(d >> 1);
			printf("0");
			return;
		}	
	}
	else
		return;
}

int power(int base, int exp){
	if(exp == 0)
		return 1;
	else
		return base*power(base, --exp);
}

int setbits(int x, int p, int n, int y){
	int y_cut, x_right_cut, i, tmp;
	i = 0;
	y_cut = 0;
	x_right_cut = 0;
	
	//obtain right cut of y and position it
	while(i < n){
		tmp = y;
		y = y >> 1;
		y = y << 1;
		if(y < tmp)
			y_cut += power(2, i);
		y = y >> 1;
		i++;
	}
	y_cut = y_cut << p;
	
	//obtain right cut of x to preserve for final OR
	i = 0;
	while(i < p){
		tmp = x;
		x = x >> 1;
		x = x << 1;
		if(x < tmp)
			x_right_cut += power(2, i);
		x = x >> 1;
		i++;
	}

	//obtain left cut of x for final or
	x = x >> n;
	x = x  << (n + p);
	return (x | y_cut | x_right_cut);

	

}

int main(){
	print_binary(setbits(0b1100101011010, 4, 3, 0b10101101001010));
}
