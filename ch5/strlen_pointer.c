//function from section 5.3; version of strlen written with pointer
#include <stdio.h>
int str_len(char *s){
	int n;
	for(n = 0; *s != '\0'; s++)
		n++;
	return n;
}

int main(){
	char s[] = "Hello World!";
	printf("Length of '%s': %d\n", s, str_len(s));
}
