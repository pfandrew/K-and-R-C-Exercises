//compile: gcc ex_1-3.c
//run: ./a.out

//Exercise 1-3: Modify the temperature conversion program to print a heading above the table.

#include <stdio.h>

int main(){
	float fahr, celsius;
	int upper, lower, step;

	upper = 300;
	lower = 0;
	step = 20;
	
	fahr = lower;
	printf("---------------\nFahr.\t Cels. \n---------------\n");
	while(fahr <= upper){
		celsius = (5.0/9.0)*(fahr - 32.0);
		printf("%3.0f\t%6.1f\n", fahr, celsius);
		fahr = fahr + step;
	}
}
