//compile: gcc ex_4-13.c
//run: ./a.out

//Exercise 4-13: Write a recursive version of the function reverse(s), which revereses the string s in place.

#include <stdio.h>
#include <string.h>

void reverse(char s[], int i){
	if(i > (strlen(s) / 2) - 1)
		return;
	int tmp = s[i];
	s[i] = s[strlen(s) - 1 - i];
	s[strlen(s) - 1 - i] = tmp;
	reverse(s, i + 1);
}

int main(){
	char string[] = "Hello World!";
	reverse(string, 0);
	printf("%s\n", string);
}
