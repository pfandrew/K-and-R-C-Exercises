//compile: gcc ex_5-3.c
//run: ./a.out

//Exercise 5-3: Write a pointer version of the function strcat that we showed in Chapter 2: strcat(s,t) copies the string t to the end of s.
#include <stdio.h>
#include <string.h>
#define MAX 20
void str_cat(char* s, char* t){
	while(*s++ != '\0')
		;
	--s;
	while((*s++ = *t++) != '\0')	
		;
}

int main(){
	char t[MAX] = "World!";
	char s[MAX] = "Hello ";
	str_cat(s,t);
	printf("Concatenated: '%s'", s);
}
