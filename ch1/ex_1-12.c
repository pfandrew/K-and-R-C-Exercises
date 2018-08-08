//compile: gcc ex_1-12.c
//run: ./a.out

//Exercise 1-12: Write a program that prints its input one word per line.

#include <stdio.h>

#define IN 1
#define OUT 0

int main(){
	int c;
	int state = OUT;
	while((c = getchar()) != EOF){
		if(c == ' ' || c == '\n' || c == '\t'){
			state = OUT;
		}
		else if (state == OUT){
			state = IN;
			printf("\n");
			putchar(c);
		}
		else if(state == IN){
			putchar(c);
		}
	}

	
}
