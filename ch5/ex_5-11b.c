//compile: gcc ex_5-11b.c
//run: ./a.out

//Exercise 5-11: Modify the programs entab and detab (written as exercises in Chapter 1) to accept a list of tab stops as arguments. Use the default tab settings if there are no arguments.

//NOTE: this is detab's modification.

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#define TAB_WIDTH 5
#define COLUMN_MAX 10

int main(int argc, char *argv[]){
	int c, i = 0, position = 0, tab_stop = 0, columns = 0;
	char *in;

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

	//regular program
	while((c = getchar()) != EOF){
		if(c == '\n'){
			printf("\n");
			position = 0;
		}
		else if(c == '\t'){
			for(i = position % tab_stop; i < tab_stop; ++i){
				if(position + (tab_stop - i) == columns*tab_stop){
					printf("\n");
					position = 0;
					break;
				}
				printf(" ");
				++position;
			}
		}
		else{
			if(position == columns*tab_stop){
				printf("\n");
				position = 0;
			}
			printf("%c", c);
			++position;
		}
	}
	return 0;
}
