//compile: gcc ex_5-4.c
//run: ./a.out

//Exercise 5-4: Write the function strend(s,t), which returns 1 if the string t occurs at the end of the string s, and zero otherwise.
#include <stdio.h>
#include <string.h>

int str_end(char* s, char* t){
	int len_t = 0;
	while(*s != '\0')
		s++;
	while(*t != '\0'){
		t++; 
		len_t++;
	}
	while(*s-- == *t-- && len_t-- > 0)
		;	
	return len_t == -1 ? 1 : 0;
}

int main(){
	char s[] = "ABJHello";
	char t[] = "Hello";
	printf("%d\n", str_end(s,t));
}
