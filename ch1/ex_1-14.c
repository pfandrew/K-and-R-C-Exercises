//compile: gcc ex_1-14.c
//run: ./a.out

//Exercise 1-14: Write a program to print a histogram of the frequencies of different characters in its input.

//NOTE: Only handles character codes for numerals and digits. Rest desginated as 'OTHER' on histogram.

#include <stdio.h>

#define NUM_CHARS     37	
#define LETTERS_BEGIN 10

int main(){

	//decl + init
	int c, i, j, largest;
	largest = 0;
	int chars[NUM_CHARS];
	for(i = 0; i < NUM_CHARS; i++)
		chars[i] = 0;

	//input
	while((c = getchar()) != EOF){
		if(c <= 57 && c >= 48) 			//numerals
			++chars[c - '0'];
		else if(c <= 90 && c >= 65) 	//uppercase letters
			++chars[LETTERS_BEGIN + c - 65];
		else if(c <= 122 && c >= 97) 	//lowercase letters
			++chars[LETTERS_BEGIN + c - 97];
		else							//other letters
			++chars[NUM_CHARS - 1];
	}

	//find largest for vertical
	for(i = 0; i < NUM_CHARS; ++i){
		if(largest < chars[i])
			largest = chars[i];
	}

	//print vertical histogram data
	for(i = 0; i <= largest; ++i){
		for(j = 0; j < NUM_CHARS; ++j){
			if(chars[j] > largest - i)
				printf("%3c", 'X');
			else
				printf("   ");
		}
		printf("\n");
	}

	//bottom of histogram
	printf("  ");
	for(i = 0; i < NUM_CHARS; ++i)
		printf("---");
	printf("\n");
	for(i = 0; i < NUM_CHARS; ++i){
		if(i < LETTERS_BEGIN){
			printf("%3c", i + '0');
		}
		else if(i < NUM_CHARS - 1)
			printf("%3c", i - LETTERS_BEGIN + 65);
		else
			printf(" OTHER\n\n");
	}
}
