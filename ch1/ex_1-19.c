//compile: gcc ex_1-19.c
//run: ./a.out

//Exercise 1-19: Write a function reverse(s) that reverse the character string s. Use it to write a program that reverses its input a line at a time.

#include <stdio.h>
#define MAX_LENGTH 1000
#define NEWLINE 1

int get_line(char s[], int lim);
void reverse(char s[], int len);

int main(){
	int len;
	char line[MAX_LENGTH];
	while((len = get_line(line, MAX_LENGTH)) > 0){
		reverse(line, len);
		printf("%s", line);
	}
}

int get_line(char s[], int lim){
	int i, c;
	for(i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i){
		s[i] = c;
	}

	if(c == '\n'){
		s[i] = c;
		++i;
	}

	s[i] = '\0';

	return i;
}

void reverse(char s[], int len){
	char tmp;
	int half, state, i, j;
	state = 0;	
	//check if newline is in input (not guaranteed in the case of string exceeding max length: see getline())
	if(s[len - 1] == '\n'){
		state = NEWLINE;	
	}
	
	//calculate stopping point for reverse
	half = (len - state) / 2;
	
	for(i = 0; i < half; ++i){
		j = len - 1 - state - i;
		tmp = s[i];
		s[i] = s[j];
		s[j] = tmp;	
	}
}
