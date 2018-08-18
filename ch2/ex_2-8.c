//compile: gcc ex_2-8.c
//run: ./a.out

//Exercise 2-8: Write a function rightrot(x,n) that returns the value of integer x rotated to the right by n bit positions.

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
int rightrot(int x, int n){
	int i = 1, len = 0, cut, accum = 0;
	if(x){
		//find length
		for(i = 1; i <= x; len++)
			i *= 2;

		//rotate one by one; could also cut and place with modulus when n > len
		for(i = 0; i < n; i++){
			if(1 & x){
				cut = (1 << accum) << (len - accum - 1);
				x = cut|(x >> 1);
				if(accum)	
					accum = 0;
			}
			else{
				x = x >> 1;
				accum++;
			}
		}	
		return x;
	}
	else
		return 0;	
}

int main(){
	print_binary(rightrot(0b1011011010, 5));
}
