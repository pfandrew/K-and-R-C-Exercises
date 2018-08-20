//compile: gcc ex_3-2.c
//run: ./a.out

//Exercise 3-2: Write a function escape(s,t) that converts characters like newline and tab into visible escape sequences like \n and \t, as it copies the string t to s. Use a switch. Write a function for the other direction as well, converting escape sequences into the real characters.

#include <stdio.h>

#define MAX 1000
#define IN 1
#define OUT 0

void escape(char s[], char t[]){
	int d, i, k;
	i = k = 0;
	d = '\\';
	while((s[k] = t[i++]) != '\0'){
		switch(s[k]){
			case '\t':
				s[k++] = d;
				s[k++] = 't';
				break; 
			case '\n': 
				s[k++] = d;
				s[k++] = 'n';
				break; 
			case '\b':
				s[k++] = d;
				s[k++] = 'b';
				break; 
			case '\a':
				s[k++] = d;
				s[k++] = 'a';
				break; 
			case '\v':
				s[k++] = d;
				s[k++] = 'v';
				break; 
			case '\f':
				s[k++] = d;
				s[k++] = 'f';
				break; 
			case '\?':
				s[k++] = d;
				s[k++] = '?';
				break; 
			default:
				k++;
		}
	}
}

void de_escape(char t[], char s[]){
	int i, k, es_state;
	i = k = es_state = OUT;
	while((t[k] = s[i++]) != '\0')
	{
		if(es_state){
			switch(t[k]){
				case '\\': t[k++] = '\\'; break;
				case 't': t[k++] = '\t';  break;
				case 'n': t[k++] = '\n';  break;
				case 'b': t[k++] = '\b';  break;
				case 'a': t[k++] = '\a';  break;
				case 'v': t[k++] = '\v';  break;
				case 'f': t[k++] = '\f';  break;
				case '?': t[k++] = '\?';  break;
				default: t[k++] = '\\'; t[k++] = s[i - 1]; break;
			}
			es_state = OUT;
		}
		else if(t[k] == '\\'){
			es_state = IN;
		}
		else{
			k++;
		}
	}
}

int main(){
	int i, c, max_s;
	i = 0;
	char t[MAX];
	max_s = MAX;
	while(i < MAX - 1 && (c = getchar()) != EOF)
	{
		t[i++] = c;
		//make sure we have enough space in s
		if(c == '\t' || c == '\n' || c == '\b' || c == '\a' || c == '\v' || c == '\f' || c == '\?')
			max_s++;
	}	
	t[i] = '\0';

	char s[max_s];

	escape(s, t);
	printf("%s\n", s);

	de_escape(t, s);
	printf("%s\n", t);
}
