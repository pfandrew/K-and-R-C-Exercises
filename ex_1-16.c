//compile: gcc ex_1-16.c
//run: ./a.out

//Exercise 1-16: Revise the main routine of the longest-line program so it will correctly print the length of arbitrarily long input lnes, and as much as possible of the text.

#include <stdio.h>
#define MAXLINE 1000

int get_line(char line[], int maxline);

int main(){

	int len, max;
	char line[MAXLINE];

	while((len = get_line(line, MAXLINE)) > 0){
		printf("LENGTH: %d\nTEXT: %s\n", len, line);
	}
	return 0;
}

int get_line(char s[], int lim){
	int c, i;

	for(i = 0; i < lim-1 && (c=getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;

	if(i == lim - 1){
		s[i] = '\0';
		while((c = getchar()) != EOF && c != '\n'){
			++i;
		}
		return i;
	}
	else if(c == '\n'){
		s[i] = c;
		++i;	
	}
	s[i] = '\0';
	return i;
}
