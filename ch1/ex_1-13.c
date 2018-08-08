//compile: gcc ex_1-13.c
//run ./a.out

//Exercise 1-13: Write a program to print a histogram of the lengths of words in its input. It is easy to draw the histogram with the bars horizontal; a vertical orientation is more challenging.

//NOTE: This solution uses a vertical orientation

#include <stdio.h>

#define MAX_LENGTH 	20
#define IN 		1
#define OUT 		0

int main(){
	
	//decl + init
	int c, i, j, length, largest, state;
	length = largest = state = 0;
	int words[MAX_LENGTH + 1];

	for(i = 0; i < MAX_LENGTH; ++i)
		words[i] = 0;

	//input
	while((c = getchar()) != EOF){
		if(c == ' ' || c == '\t' || c == '\n'){
			state = OUT;
			++words[length];
			length = 0;
		}
		else if(state == OUT){
			state = IN;
			++length;
		}
		else if(state == IN){
			++length;
		}
	}

	//find largest vertical tower
	for(i = 1; i <= MAX_LENGTH; ++i){
		if(largest < words[i]){
			largest = words[i];
		}
	}

	printf("\n\n");
	
	//print histogram data
	for(i = 1; i <= largest; ++i){
		for(j = 1; j <= MAX_LENGTH; ++j){
			if(words[j] > largest - i){
				printf("%3c", 'X');
			}
			else
				printf("   ");
		}
		printf("\n");
	}
	
	//histogram footer
	printf(" ----------------------------------------------------------\n");
	for(i = 1; i <= MAX_LENGTH; ++i)
		printf("%3d", i);
	printf("\n");
}
