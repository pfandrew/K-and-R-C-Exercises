//compile: gcc ex_1-22.c
//run: ./a.out

//Exercise 1-22: Write a program to "fold" long input lines into two or more shorter lines after the last non-blank character that occurs before the n-th column of input. Make sure your program does something intelligent with very long lines, and if there are no blanks or tabs before the specified column.

#include <stdio.h>

#define WRAP_AT 40
#define TAB_STOP 8
#define NO_BLANK -1

int main(){
	int i, k, c, column, last_blank;
	i = k = column = last_blank  = 0;
	last_blank = NO_BLANK;

	char line[WRAP_AT + 3];

	while((c = getchar()) != EOF){
		last_blank = NO_BLANK;
		while(column < WRAP_AT && c != '\n' && c != EOF){
			//printf("%c", line[column]);
			if(c == ' '){
				last_blank = column;
				line[column] = c;
				++column;
			}
			else if(c == '\t'){
				last_blank = column;
				for(i = 0; i < TAB_STOP; ++i){
					line[i + column] = ' ';
				}
				column += i;
			}
			else{
				line[column] = c;
				++column;
			}
			c = getchar();
	
		}

		if(c == ' ' || c == '\t' || c == '\n'){
			line[column] = '\n';
			++column;
			line[column] = '\0';
			printf("%s", line);
			column = 0;
		}
		else if(last_blank != NO_BLANK){
			for(i = 0; i < last_blank; ++i){
				printf("%c", line[i]);
			}
			printf("\n");
			line[0] = c;
			column = 1;
		}
		else if(c == EOF){
			break;
		}
		else {
			line[column] = '-';
			++column;
			line[column] = '\n';
			++column;
			line[column] = '\0';
			printf("%s", line);
			column = 0;
			line[column] = c;
			++column;
		}
	}	
	return 0;
}
