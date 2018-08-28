//compile: gcc ex_5-11b.c
//run: ./a.out

//Exercise 5-11: Modify the programs entab and detab (written as exercises in Chapter 1) to accept a list of tab stops as arguments. Use the default tab settings if there are no arguments.

//NOTE: this is entab's modification.

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define TAB_WIDTH 5
#define COLUMN_MAX 10
#define IN_TAB_WIDTH 4
#define MAX_LENGTH 1000

int main(int argc, char *argv[]){
	int i = 0, c, blanks = 0, position = 0, columns = 0, tab_stop = 0;
	char input[MAX_LENGTH];

	//grab tab stops
	if(argc == 1){	
		tab_stop = TAB_WIDTH;
		columns = COLUMN_MAX;
	}
	else{
		while(--argc > 0 && *++argv){
			if(isdigit(**argv)){
				if(!tab_stop)
					tab_stop = atoi(*argv);
				else if(!columns)
					columns = atoi(*argv);
				else
					break;	
				
			}
			else
				printf("Usage: detab [tab_width]");
		}
	}

	while(i < MAX_LENGTH - 1 && (c = getchar()) != EOF){
		if(c == '\n'){
			position = 0;
			blanks = 0;
			input[i] = c;
			++i;
		}
		else if(c == ' ' || c == '\t'){
			if(c == ' ')
				++blanks;
			else{
				blanks += IN_TAB_WIDTH - ((blanks + position) % IN_TAB_WIDTH);
			}
		}
		else if(blanks){
			
			if(blanks + position >= columns*tab_stop){
				printf("\n");
				position = 0;
			}
			else{
				//place tabs
				while(blanks >= tab_stop - (position % TAB_WIDTH))	
				{
					//place tab
					input[i] = '\t';
					++i;
					blanks = blanks - (tab_stop - (position % tab_stop));
					position = 0; 
				}
				while(blanks > 0){
					input[i] = ' ';
					--blanks;
					++i;
				}
			}
		}

		if(c != ' ' && c != '\n' && c != '\t'){
			if(position >= columns*tab_stop){
				printf("\n");
				position = 0;
			}
			++position;
			input[i++] = c;
		}		
	}
	input[i] = '\0';
	
	//this prints the input with a tabstop length of 8 on my terminal. every \t encoded above is longer than what the program anticipates.
	printf("%s\n\n", input);

	return 0;
}
