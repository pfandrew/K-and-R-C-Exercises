//functions from section 5.5; compares lexicographic value of two strings
#include <stdio.h>

int str_cmp_arr(char s[], char t[]){
	int i;
	for(i = 0; s[i] == t[i]; i++){
		if(s[i] == '\0'){
			return 0;
		}
	}
	return s[i] - t[i];
}

int str_cmp_ptr(char* s, char* t){
	while(*s++ == *t++){
		if(*s == '\0') 
			return 0;
	}
	return *--s - *--t;
}

int main(){
	char s[] = "Hello World!";
	char t[] = "Jello Whirled!";
	int d;
	d = str_cmp_arr(s, t) < 0 ? printf("'%s' < '%s'\n", s, t) : (d == 0 ? printf("'%s' == '%s'\n", s, t) : printf("'%s' > '%s'\n", s, t)); 
	d = str_cmp_ptr(s, t) < 0 ? printf("'%s' < '%s'\n", s, t) : (d == 0 ? printf("'%s' == '%s'\n", s, t) : printf("'%s' > '%s'\n", s, t)); 
}
