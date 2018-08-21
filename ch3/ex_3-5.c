//compile: gcc ex_3-5.c
//run: ./a.out

//Exercise 3-5: Write the function itob(n,s,b) that converts the integer n into a base b character representation in the string s. In particular, itob(n,s,16) formats n as a hexadecimal integer in s.
#include <stdio.h>
#include <string.h>
#define MAX 1000
#define POS 1
#define NEG -1

void reverse(char s[]){
	int i, j, tmp;
	for(i = 0, j = strlen(s) - 1; i < j; i++, j--){
		tmp = s[i], s[i] = s[j], s[j] = tmp;
	}
}

void itob(int n, char s[], int b){
	if(b > 36 || b < 2){
		printf("Base-%d not supported\n", b);
		return;
	}

	int i, d, sign;
	if(n < 0)
		sign = NEG;
	else
		sign = POS;

	i = 0;

	do {
		if((d = sign*(n % (sign*b)) + '0') >= 58)
			s[i++] = d + 7; //get access to uppercase letters
		else
			s[i++] = d; 
	} while((n /= b) != 0);

	if(sign == NEG)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

int main(){
	char num[MAX];
	itob(-128, num, 16);
	printf("%d in Hex: %s\n", -128, num);
	itob(45, num, 2);
	printf("%d in Binary: %s\n", 45, num);
	itob(15, num, 8);
	printf("%d in Octal: %s\n", 15, num);
	
}
