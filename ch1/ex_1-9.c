//compile: gcc ex_1-9.c
//run: ./a.out

//Exercise 1-9: Write a program to copy its input to its output, replacing each string of one or more blanks by a single blank.

#include <stdio.h>

int main(){
	int c, blanks;
	blanks = 0;
	while((c = getchar()) != EOF){
		if(blanks){
			while(c == ' '){
				c = getchar();
			}
			blanks = 0;
		}
		else if(c == ' '){
			blanks = 1;
		}
		putchar(c);
	}
}
