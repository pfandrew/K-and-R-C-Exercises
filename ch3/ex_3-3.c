//compile: gcc ex_2-3.c
//run: ./a.out

//Exercise 2-3: Write a function expand(s1,s2) that expands a shorthand notations like a-z in the string s1 into the equivalent list abc...xyz in s2. All for letters of either case and digits, and be prepared to handle cases like a-b-c and a-z0-9 and -a-z. Arrange that a leading or trailing - is taken literally.

#include <stdio.h>
#define MAX 1000

int state(char c){
	return 0b111 & ((c >= 97 && c <= 122) << 2 | (c >= 65 && c <= 90) << 1 | (c - '0' >= 0 && c - '0' <= 9));
}

void expand(char s1[], char s2[]){
	int c, d, e, i, k;
	for(i = 0, k = 0; i < MAX - 1 && k < MAX - 1 && (c = s1[i++]) != '\0' ;){
		if(c == '-' && k > 0){
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

