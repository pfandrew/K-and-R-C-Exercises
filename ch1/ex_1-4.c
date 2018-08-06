//compile: gcc ex_1-4.c
//run: ./a.out

//Exercise 1-4: Write a program to print the corresponding Celsius to Fahrenheit table.

#include <stdio.h>

int main(){
	float fahr, celsius;
	int upper, lower, step;

	upper = 149;
	lower = -18;
	step = 11;

	celsius = lower;
	
	printf("---------------\nCels.\t Fahr.\n---------------\n");
	while(celsius <= upper){
		fahr = (celsius * (9.0/5.0)) + 32;
		printf("%3.0f\t%6.1f\n", celsius, fahr);
		celsius = celsius + 11;
	}
}
