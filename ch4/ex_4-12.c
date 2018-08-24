//compile: gcc ex_4-12.c
//run: ./a.out

//Exercise 4-12: Adapt the ideas of printd to write a recursive version of itoa; that is, convert an integer into a string by calling a recursive routine

#include <stdio.h>

#define POS 1
#define NEG -1
#define MAX_LEN 100

int itoa(char s[], int d, int i){
	int sign = POS;
	if(d < 0 && i == 0){
		s[i++] = '-';
		sign = NEG;
	}
	if(sign*(d / 10)){
		i = itoa(s, sign*(d/10), i);
	}
	s[i] = sign*(d % (sign*10)) + '0';
	return i + 1;	
}


int main(){
	char num_string[MAX_LEN];
	int len = itoa(num_string, 8765, 0);
	num_string[len] = '\0';
	printf("%s\n", num_string);
}
