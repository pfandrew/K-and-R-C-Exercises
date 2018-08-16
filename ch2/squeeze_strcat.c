//functions from section 2.8
//squeeze() removes all characters 'c' from string 's'
//str_cat() concatenates  the string 't' to the end of the string 's'

#include <stdio.h>

void squeeze(char s[], int c){
	int i, j;
	for(i = j = 0; s[i] != '\0'; i++){
		if(s[i] != c)
			s[j++] = s[i];
	}
	s[j] = '\0';
}

void str_cat(char s[], char t[]){
	int i, j;
	i = j = 0;
	while(s[i] != '\0')
		i++;
	while((s[i++] = t[j++]) != '\0')
		;
}

int main(){
	char s[15] = "Hello ";
	char s2[76] = "World!";
	printf("Original string: '%s'\n", s);
	squeeze(s, 'l');
	printf("After squeeze('l'): '%s'\n", s);
	str_cat(s, s2);
	printf("After concatenation of another string: '%s'\n", s);
	
}
