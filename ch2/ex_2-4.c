//compile: gcc ex_2-4.c
//run: ./a.out

//Exercise 2-4: Write an alternate version of squeeze(s1, s2) that deletes each character in s1 that matches any character in the string s2

#include <stdio.h>
#define MAX 1000

void squeeze(char s[], int c){
	int i, j;
	for(i = j = 0; s[i] != '\0'; i++){
		if(s[i] != c)
			s[j++] = s[i];
	}
	s[j] = '\0';
}

void squeeze_alt(char s[], char t[]){
	int i;
	for(i = 0; t[i] != '\0'; i++)
		squeeze(s, t[i]);
}

int main(){
	int i, c;
	i = 0;
	char s[MAX];
	char t[MAX];
	
	//input both strings
	printf("Input first string: ");
	while(i < MAX - 1 && (c = getchar()) != '\n' && c != EOF)
		s[i++] = c;
	s[i] = '\0';

	i = 0;
	printf("Input second string: ");
	while(i < MAX - 1 && (c = getchar()) != '\n' && c != EOF)
		t[i++] = c;
	t[i] = '\0';

	squeeze_alt(s, t);

	printf("Result: %s\n", s);
	return 0;
}
