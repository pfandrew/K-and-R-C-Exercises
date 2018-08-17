//compile: ex_2-5.c
//run: ./a.out

//Exercise 2-5: Write the function any(s1, s2), which returns the first location in the string s1 where any character from the string s2 occurs, or -1 if s1 contains no characters from s2. (The standard library function strpbrk does the same job but returns a pointer to the location.)

#include <stdio.h>
#define MAX 1000

int find_first(char s[], int c){
	int i, d;
	i = 0;
	while((d = s[i++]) != c && d != '\0')
		;

	if(d != '\0')
		return --i;
	else 
		return -1;
}

int any(char s1[], char s2[]){
	int i, c, k;
	i = 0;
	while((c = s2[i++]) != '\0'){
		if((k = find_first(s1, c)) + 1)
			return k;
	}
	return -1;
}

int main(){
	int c, i, loc;
	i = 0;
	char s1[MAX];
	char s2[MAX];
	printf("Enter first string: ");
	while(i < MAX - 1 && (c = getchar()) != '\n' && c != EOF)
		s1[i++] = c;
	s1[i] = '\0';

	i = 0;
	printf("Enter second string: ");
	while(i < MAX - 1 && (c = getchar()) != '\n' && c != EOF)
		s2[i++] = c;
	s2[i] = '\0';
	
	loc = any(s1, s2);
	printf("First location (0-indexed) of any character from s2 in s1: %d\n", loc);
	return 0;
}
