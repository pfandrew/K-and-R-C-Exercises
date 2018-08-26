//compile: ex_5-5.c
//run: ./a.out

//Exercise 5-5: Write versions of the library functions strncpy, strncat, and strncmp, which operate on at most the first n characters of their argument strings. For example, strncpy(s,t,n) copies at most n characters of to to s. Full descriptions are in Appendix B.

#include <stdio.h>

//copy at most n characters of ct to s; return s. Pad with '\0's if t has fewer than n characters.
char* str_ncpy(char* s, char* ct, int n){
	int k = n;
	while(n-- > 0 && ct != '\0')
		*s++ = *ct++;
	while(n-- > 0)
		*s++ = '\0';
	return s - k;
}

//concatenate at most n characters of string s ct to string s, terminate with '\0'; return s.
char* str_ncat(char* s, char* ct, int n){
	int k = 0;
	while(*s != '\0'){
		s++; 
		k++;
	}
	while(*ct != '\0' && n-- > 0)
	{	
		*s++ = *ct++;
		k++;
	}
	*s = '\0';
	return s - k;
}


//compare at most n characters of string cs to string ct; return < 0 if cs < ct, 0 if cs == ct, or > 0 if cs > ct.
int str_ncmp(char* cs, char* ct, int n){
	while(*cs == *ct && --n > 0){
		cs++, ct++;
	}
	return (*cs - *ct);
		
}

int main(){
	//str_ncpy test
	char ct[] = "Helo";
	char s[20];
	printf("%s\n", str_ncpy(s,ct,3));	

	//str_ncat test
	char ct2[] = "World!";
	char s2[20] = "Hello ";
	printf("%s\n", str_ncat(s2, ct2, 3));	

	//str_ncmp test
	char cs[] = "HelLo!";
	char ct3[] = "Hell";
	printf("%d\n", str_ncmp(cs, ct3, 4));
}
