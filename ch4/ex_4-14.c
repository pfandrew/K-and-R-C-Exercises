//compile: gcc ex_4-14.c
//run: ./a.out

//Exercise 4-14: Define a macro swap(t,x,y) that interchanges two arguments of type t. (Block structure will help.)

#include <stdio.h>

#define swap(t,x,y) {  \
			if(sizeof(t) == sizeof(y) && sizeof(t) == sizeof(x)){ \
				t var = y; \ 
		 		y = x;	   \ 
				x = var;   \
			}}						

int main(){
	int A = 5;
	int B = 2;
	printf("Original X: %d, Original Y: %d\n", A, B);
	swap(int, A, B)
	printf("After swap X: %d, After swap Y: %d\n", A, B);

	
}
