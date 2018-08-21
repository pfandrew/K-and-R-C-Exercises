//compile: gcc ex_3-6.c
//run: ./a.out

//Exercise 3-6: Write a version of itao that accepts three arguments instead of two. The third argument is a minimum field width; the converted number must be padded with blanks on the left if necessary to make it wide enough.


#include <stdio.h>
#include <string.h>
#define MAX 1000
#define NEG -1
#define POS  1

void reverse(char s[]){
	int i, j, tmp;
	for(i = 0, j = strlen(s) - 1; i < j; i++, j--){
		tmp = s[i], s[i] = s[j], s[j] = tmp;
	}
}

void itoa(int n, char s[], int min_width){
	int i; 
	int sign, d;

	if(n < 0)
		sign = NEG;
	else
		sign = POS;

	i = 0;
	
	do {
		s[i++] = sign*(n % (sign*10)) + '0';
	} while ((n /= 10) != 0);

	while(i < min_width)
		s[i++] = ' ';	
	if(d = sign == NEG)
		s[--i] = '-';
	s[i+d] = '\0';
	reverse(s);
}

int main(){
	char num[MAX];
	
	itoa(36, num, 7);
	printf("%s\n", num);
	itoa(100328739, num, 7);
	printf("%s\n", num);
	itoa(-89, num, 7);
	printf("%s\n", num);
}
