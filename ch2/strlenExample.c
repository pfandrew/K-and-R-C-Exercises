//function str_len as from Section 2.3; Counts length of a string

#include <stdio.h>
#define MAX 1000
int str_len(char s[]){
	int i;
	i = 0;
	while(s[i] != '\0')
		++i;
	return i;
}

int main(){
	int i, c, len;
	i = len = 0;
	char input[MAX];
	
	while(i < MAX - 1){
		c = getchar();
		if(c == '\n' || c == EOF){
			input[i] = '\0';
			if((len = str_len(input)))	
				printf("String: '%s'\nLength: %d\n", input, len);
			if(c == EOF)
				i = MAX;
			else
				i = 0;
		}
		else{
			input[i] = c;
			i++;
		}
	}
	return 0;
}
