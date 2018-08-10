//compile: gcc ex_1-18.c
//run ./a.out

//Exercise 1-18: Write a program to remove trailing blanks and tabs from each line of input, and to delete entirely blank lines.

//NOTE: Similar to previous exercise, this can be done in two ways: handle all user input at once, or handle it line by line. This program handles it line by line and removes the newline at the end of each input, so it can be seen by the cursor position during input that trailing blanks and tabs are actually removed from previous input to the terminal.

#include <stdio.h>
#define MAX_LENGTH 1000

int get_line(char input_buffer[], int max_length);

int main(){
	int i, len;
	i  = len = 0;
	char line[MAX_LENGTH];
	
	while((len = get_line(line, MAX_LENGTH)) >= 0){
		printf("%s", line);
	}
}

int get_line(char i_buf[], int max_len){
	int i, j, c;
	i = j = 0;

	for( i = 0; i < max_len - 1 && (c = getchar()) != EOF && c != '\n'; ++i){
		i_buf[i] = c;
	}
	

	if(c == EOF){
		return -1;
	}
	if(c == '\n'){
		i_buf[i] == '\n';
	}

	//find trailing blanks/tabs as well as entirely blank lines (only '\n')
	j = i - 1;
	while((i_buf[j] == '\t' || i_buf[j] == ' ' || i_buf[j] == '\n') && j >= 0){
		i_buf[j] = '\n';
		--j;
	}
	
	++j;
	i_buf[j] = '\0';

	return j;
}

