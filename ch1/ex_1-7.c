//compile: ex_1-7.c
//run: ./a.out

//Exercise 1-7: Write a program to print the value of EOF.

#include <stdio.h>

int main(){
	int c;
	while((c = getchar()) != EOF){
	}

	printf("EOF value: %d\n", c);
}
