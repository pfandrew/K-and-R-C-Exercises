//compile: gcc ex_1-20.c
//run: ./a.out

//Exercise 1-20: Write a program detab that replaces tabs in the input with the proper number of blanks to space to the next tab stop. Assume a fixed set of tab stops, say every n columns. Should n be a variable or a symbolic parameter?

#include <stdio.h>
#define TAB_WIDTH 5

int main(){
	int c, i, column;
	column = 0;
	
	while((c = getchar()) != EOF){
		if(c == '\n'){
			printf("\n");
			column = 0;
		}
		else if(c == '\t'){
			for(i = column % TAB_WIDTH; i < TAB_WIDTH; ++i){
				printf(" ");
				++column;
			}
		}
		else{
			printf("%c", c);
			++column;
		}
	}
	return 0;
}
