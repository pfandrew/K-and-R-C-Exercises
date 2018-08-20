//compile: gcc ex_2-3.c
//run: ./a.out

//Exercise 2-3: Write a function expand(s1,s2) that expands a shorthand notations like a-z in the string s1 into the equivalent list abc...xyz in s2. All for letters of either case and digits, and be prepared to handle cases like a-b-c and a-z0-9 and -a-z. Arrange that a leading or trailing - is taken literally.

/*
	token 1: uppercase letter, lowercase letter, digit
	token 2: -
	token 3: if no token, do not expand. if token is not of same type, do not expand. if token is of same type, expand to that location

	engine algorithm:
		grab token
		looking for other end of expansion?
		looking for hyphen?
		ucase letter?
			place in s2
			look for hyphen and ucase
		lcase letter?
			place in s2
		digit?
*/

#include <stdio.h>
#define MAX 1000
#define IN 1
#define OUT 0
#define UPPER 0b100
#define LOWER 0b010
#define DIGIT 0b001

int state(char c){
	return 0b111 & ((c >= 97 && c <= 122) << 2 | (c >= 65 && c <= 90) << 1 | (c - '0' >= 0 && c - '0' <= 9));
}

void expand(char s1[], char s2[]){
	int c, d, e, i, k;
	for(i = 0, k = 0; i < MAX - 1 && k < MAX - 1 && (c = s1[i++]) != '\0' ;){
		if(c == '-' && i > 0 && k > 0){
			d = s2[k-1];
			e = s1[i];
			if(state(d) && (state(d) == state(e)) && d < e){
				i++;
				while(d++ < e && k < MAX - 1){
					s2[k++] = d;
				}
			}
		}
		else
			s2[k++] = c;
	}
	s2[k] = '\0';
}

int main(){
	int c, i;
	i = 0;
	char input[MAX];
	char expansion[MAX];
	while((c = getchar()) != EOF){
		input[i++] = c;
	}
	input[i] = '\0';
	expand(input, expansion);
	printf("%s\n", expansion);
}

