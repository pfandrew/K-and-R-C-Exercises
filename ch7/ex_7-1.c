//compile: gcc ex_7-1.c -o upper
//compile: gcc ex_7-1.c -o lower
//run: ./upper
//run: ./lower

//Exercise 7-1: Write a program that converts upper case to lower case or lower case to upper, depending on the name it is invoked with, as found in argv[0].

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXINPUT 10000

int main(int argc, char *argv[]){
	int (*fn)(int), i = 0, c;
	char input[MAXINPUT];
	
	if(strcmp("./lower", *argv) == 0){
		fn = &tolower;
	}
	else
		fn = &toupper;
	
	while((c = getchar()) != EOF){
		input[i++] = (*fn)(c);
	}

	input[i] = '\0';
	printf("\n%s\n", input);
		
}
