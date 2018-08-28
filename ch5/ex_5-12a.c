//compile: gcc ex_5-12b.c
//run: ./a.out

/*Exercise 5-12: Extend entab and detab to accept the shorthand
	
	entab -m -n

to mean tab stops every n columns, starting at column m. Choose convenient (for the user) default behavior. */


//NOTE: this is entab's modification.

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#define TAB_WIDTH 5
#define COLUMN_MAX 5
#define MAX_LENGTH 1000

int main(int argc, char *argv[]){
	int c, i = 0, line_position = 0, tab_position = 0, tab_width_in = 0, columns = COLUMN_MAX, column_start = 0, tab_stop = TAB_WIDTH, blanks = 0;
	char input[MAX_LENGTH];	
	while(--argc > 0 && *++argv){
		c = *(*argv)++;
		if(c == '-' || c == '+'){
			if(c == '-'){
				column_start = atoi(*argv);
				continue;
			}
			else{
				tab_width_in = atoi(*argv);
				continue;
			}
		}
	}
	int maxline, start = 0, past_start = 0;

	if(column_start && tab_width_in){
		maxline = (columns - column_start)*tab_width_in + (column_start*TAB_WIDTH);	
		start = column_start*TAB_WIDTH;
	}
	else if(tab_width_in)
		maxline = COLUMN_MAX*tab_width_in;
	else{
		tab_width_in = TAB_WIDTH;
		maxline = COLUMN_MAX*TAB_WIDTH;
	}
	//entab
	while((c = getchar()) != EOF){
		if(line_position >= start)
			past_start = 1;

		if(c == '\n'){
			input[i++] = c;
			line_position = 0;
			blanks = 0;
			past_start = 0;
			continue;
		}
		else if (c == ' '|| c == '\t'){
			if(c == '\t'){ 
				if(tab_width_in)
					tab_stop = past_start ? tab_width_in : TAB_WIDTH;
				tab_position = (line_position - (past_start*start)) % tab_stop;
				blanks += tab_stop - tab_position;
			}
			else
				blanks++;
			continue;
		}
		else if(blanks){
			if(line_position + blanks >= maxline){
				input[i++] = '\n';
				line_position = 0;
				past_start = 0;
			}
			else{
				//first deal with pre-user specified column blanks
				if(!past_start){
					tab_position = line_position % TAB_WIDTH;
					while(blanks >= tab_stop && !past_start){
						input[i++] = '\t';
						blanks -= (TAB_WIDTH - tab_position);
						line_position += (TAB_WIDTH - tab_position);
						tab_position = 0;
						if(line_position >= start)
							past_start = 1;
					}
					while(blanks > 0 && !past_start){
						input[i++] = ' ';
						blanks--;
						line_position++;
					}
				}
				//now deal with blanks that occur after user specified column, if any
				while(blanks >= tab_width_in){
						input[i++] = '\t';
						blanks -= (tab_width_in - tab_position);
						line_position += (tab_width_in - tab_position);
						tab_position = 0;
				}
				while(blanks > 0){
					input[i++] = ' ';
					blanks--;
					line_position++;
				}
			}
			blanks = 0;
		}

		if(line_position >= maxline){
			input[i++] = '\n';
			line_position = 0;
			blanks = 0;
			past_start = 0;
		}
	
		input[i++] = c;
		++line_position;
	}
		
	input[i] = '\0';
	tab_stop = TAB_WIDTH;
	line_position = tab_position = 0;
	i = 0;
	int k = 0;
/*test with detab, since output to terminal will output its own tab length, not the users*/
	//detab
	while((c = input[i++]) != '\0'){
		if(c == '\n'){
			printf("\n");
			line_position = 0;
		}
		else if(c == '\t'){
			tab_position = line_position % tab_stop;
			if(tab_width_in > 0){
				tab_stop = line_position >= column_start*TAB_WIDTH ? tab_width_in : TAB_WIDTH;
			}
			
			if(line_position + (tab_stop - tab_position) >= maxline){
				printf("\n");
				line_position = 0;
			}
			else{
				for(k = tab_position; k < tab_stop; ++k){
					printf(" ");
					++line_position;
				}
			}
		}
		else{
			if(line_position >= maxline){
				printf("\n");
				line_position = 0;
			}
			printf("%c", c);
			++line_position;
		}
	}	
	return 0;
}
