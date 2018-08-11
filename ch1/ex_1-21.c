//compile: gcc ex_1-21.c
//run ./a.out

//Exercise 1-21: Write a program entab that replaces strings of blanks by the minimum number of tabs and blanks to achieve the same spacing. Use the same tab stops for detab. When either a tab or a single blank would suffice to reach a tab stop, which should be given preference?

//NOTE: There's no directive for dealing with tabs as they are input. Should the inputted tabs be counted as blanks according to the tab stops of the input, or according to the tab stop length defined within the program? It is assumed that input tabs are of length '4'.	

#include <stdio.h>
#define TAB_WIDTH 5
#define IN_TAB_WIDTH 4
#define MAX_LENGTH 1000

int main(){
	int i, c, blanks, column;
	char input[MAX_LENGTH];
	i = blanks = column = 0;

	while(i < MAX_LENGTH - 1 && (c = getchar()) != EOF){
		if(c == '\n'){
			column = 0;
			blanks = 0;
			input[i] = c;
			++i;
		}
		else if(c == ' ' || c == '\t'){
			if(c == ' ')
				++blanks;
			else{
				blanks += IN_TAB_WIDTH - ((blanks + column) % IN_TAB_WIDTH);
			}
		}
		else if(blanks){
			
			//place tabs
			while(blanks >= TAB_WIDTH - (column % TAB_WIDTH))	
			{
				//place tab
				input[i] = '\t';
				++i;
				blanks = blanks - (TAB_WIDTH - (column % TAB_WIDTH));
				column = 0; 
			}
			while(blanks > 0){
				input[i] = ' ';
				--blanks;
				++i;
			}
		}

		if(c != ' ' && c != '\n' && c != '\t'){
			++column;
			input[i] = c;
			++i;
		}		
	}
	input[MAX_LENGTH - 1] = '\0';
	


	//this prints the input with a tabstop length of 8 on my terminal. every \t encoded above is longer than what the program anticipates.
	printf("%s\n\n", input);



	
	//This program can also  be tested by running it through the previous program, which should ensure that it is working correctly, since the tab stop length is defined the same
/*	int k = 0;
	i = c = column = 0;
	while((c = input[k]) != '\0'){
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
	++k;
	}

*/	


	return 0;
}
