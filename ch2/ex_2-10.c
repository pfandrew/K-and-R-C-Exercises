//compile: gcc ex_2-10.c
//run: ./a.out

//Exercise 2-10: Rewrite the function lower, which converts upper case letters to lower case, with a conditional expression instead of if-else.
#include <stdio.h>
#define MAX 1000

int lower(int c){
	return c >= 'A' && c <= 'Z' ? c + 'a' - 'A' : c;
}

int main(){
	int i, c;
	i = 0;
	char input[MAX];
	while(i < MAX - 1 && (c = getchar()) != '\n')
		input[i++] = lower(c);
	
	input[i] = '\0';
	printf("%s\n", input);
}
