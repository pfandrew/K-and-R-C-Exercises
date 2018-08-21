//compile: gcc ex_4-1.c
//run: ./a.out

//Exercise 4-1: Write the function strrindex(s,t), which returns the position of the rightmost occurrence of t in s, or -1 if there is none

//NOTE: The solution requires only a minor change to the previously implemented str_index() function. Another faster solution could involve going backwards through the provided strings in strrindex.

#include <stdio.h>
#define MAXLINE 1000

int get_line(char line[], int max);
int strrindex(char source[], char searchfor[]);

char pattern[] = "ould";

int main()
{
	char line[MAXLINE];
	int d = 0;
	while(get_line(line, MAXLINE) > 0){
		if((d = strrindex(line, pattern)) >= 0){
			printf("%d\n", d);
		}
	}
}

int get_line(char s[], int lim)
{
	int c, i;
	i = 0;
	while(--lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;
	if(c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

int strrindex(char s[], char t[])
{
	int i, j, k, last = -1;
	for(i = 0; s[i] != '\0'; i++){
		for(j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
			;
		if(k > 0 && t[k] == '\0')
			last = i;
	}
	return last;
}
