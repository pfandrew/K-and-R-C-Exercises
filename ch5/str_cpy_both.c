//examples from section 5.5; copies string t into s
#include <stdio.h>
#include <string.h>
void str_cpy_arr(char s[], char t[]){
	int i;
	i = 0;
	while((s[i] = t[i]) != '\0')
		i++;
}

void str_cpy_ptr(char* s, char* t){
	while(*s++ = *t++)
		;	
}

int main(){
	char t[] = "Hello World!";
	char s[strlen(t)];
	str_cpy_arr(s, t);
	printf("S after copy: %s\n", s);
	char q[] = "Jello Hurled!";
	char p[strlen(q)];
	str_cpy_ptr(p, q);
	printf("P after copy: %s\n", p);
}
