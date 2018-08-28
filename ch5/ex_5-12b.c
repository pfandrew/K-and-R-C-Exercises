//compile: gcc ex_5-12b.c
//run: ./a.out

/*Exercise 5-12: Extend entab and detab to accept the shorthand
	
	entab -m -n

to mean tab stops every n columns, starting at column m. Choose convenient (for the user) default behavior. */


//NOTE: this is detab's modification.

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#define TAB_WIDTH 5
#define COLUMN_MAX 5

int main(int argc, char *argv[]){
	int c, i = 0, line_position = 0, tab_position = 0, tab_width_in = 0, columns = COLUMN_MAX, column_start = 0, tab_stop = TAB_WIDTH;
	char *in;

	
	while(--argc > 0 && *++argv){
		c = *(*argv)++;
		if(c == '-' || c == '+'){
			if(c == '-'){
				column_start = atoi(*argv);
				printf("%d", column_start);
				continue;
			}
			else{
				tab_width_in = atoi(*argv);
				printf("%d", tab_width_in);
				continue;
			}
		}
	}	

	//default
	if(!tab_width_in)
		tab_width_in = TAB_WIDTH;

	//regular program
	while((c = getchar()) != EOF){
		if(c == '\n'){
			printf("\n");
			line_position = 0;
		}
		else if(c == '\t'){
			tab_position = line_position % tab_stop;
			if(tab_width_in)
				tab_stop = line_position >= column_start*TAB_WIDTH ? tab_width_in : TAB_WIDTH;
			for(i = tab_position; i < tab_stop; ++i){
				if(line_position + (tab_stop - i) == columns*tab_stop){
					printf("\n");
					line_position = 0;
					break;
				}
				printf(" ");
				++line_position;
			}
		}
		else{
			if(line_position >= columns*tab_stop){
				printf("\n");
				line_position = 0;
			}
			printf("%c", c);
			++line_position;
		}
	}
	return 0;
}
