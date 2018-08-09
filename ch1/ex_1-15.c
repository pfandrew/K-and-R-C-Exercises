//compile gcc ex_1-15.c
//run: ./a.out

//Exercise 1-15: Rewrite the temperature conversion program of Section 1.2 to use a function for conversion.

#include <stdio.h>

#define STEP 	20
#define UPPER 	300
#define LOWER 	0

float conversion(int n){
	return (5.0/9.0) * (n - 32.0);
}

int main(){
	printf("Fahr.\t Cels.\n");
	for(int i = LOWER; i <= UPPER; i = i + STEP)
		printf("%3d\t%6.1f\n", i, conversion(i));
	return 0;
}
