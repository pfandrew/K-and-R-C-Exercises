//compile: gcc ex_1-17.c
//run: ./a.out

//Exercise 1-17: Write a program to print all input lines that are longer than 80 characters.

//NOTE: There are 2 ways to do this: 1) Immediately reprint inputs greater than 80 characters or 2) Allow user to enter all input lines, then reprint only those which are greater than 80 characters. This is a solution for 1).

#include <stdio.h>
#define MAXLINE 1000
#define MIN2PRINT 80

int get_line(char line[], int maxline);

int main(){

	int len, max;
	char line[MAXLINE];

	while((len = get_line(line, MAXLINE)) > 0){
		if(len > MIN2PRINT)
			printf("%s\n", line);
		else
			printf("Input line not longer than 80 characters.\n");
	}
	return 0;
}

int get_line(char s[], int lim){
	int c, i;

	for(i = 0; i < lim-1 && (c=getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if(c == '\n'){
		s[i] = c;
		++i;	
	}
	s[i] = '\0';
	return i;
}
