//example from section 3.6
//converts an integer to a string

#include <stdio.h>
#include <string.h>
#define MAX 1000

void reverse(char s[]){
	int i, j, tmp;
	for(i = 0, j = strlen(s) - 1; i < j; i++, j--){
		tmp = s[i], s[i] = s[j], s[j] = tmp;
	}
}

void itoa(long int n, char s[]){
	int i; 
	long int sign;

	if((sign = n) < 0)
		n = -n;

	i = 0;
	do {
		s[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);
	if(sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

int main(){
	char num[MAX];
	
	itoa(-768, num);
	printf("%s\n", num);
	itoa(-30984, num);
	printf("%s\n", num);
	itoa(239793478390, num);
	printf("%s\n", num);
	itoa(0, num);
	printf("%s\n", num);
}
