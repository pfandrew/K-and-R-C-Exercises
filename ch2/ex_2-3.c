//compile: gcc ex_2-3.c
//run ./a.out

//Exercise 2-3: Write the function htoi(s), which converts a string of hexadecimal digits (including an optional 0x or 0X) into its equivalent integer value. The allowable digits are 0 through 9, a through f, and A through F.

#include <stdio.h>
#define MAX 1000
#define FALSE 	0
#define TRUE  	1
#define UPPER	55
#define LOWER	87
#define NUMBER	48

long int h2d(char hex[]){
	int i, c, upper, lower, number;
	upper = lower = number = FALSE;
	long int n = 0;
	if(hex[0] == '0' && (hex[1] == 'X' || hex[1] == 'x'))
		i = 2;
	else
		i = 0;

	for(; ((c = hex[i++]) != '\0' && ((upper = c >= 'A' && c <= 'F') || (lower = c >= 'a' && c <= 'f') || (number = c >= '0' && c <= '9')));){

		n = n * 16 + (c - (UPPER*upper) - (LOWER*lower) - (NUMBER*number));
		upper = lower = number = FALSE;
	}

	if(c != '\0'){
		printf("Error at pos %d of input: '%c' is not a number or hex digit. Stopping...\n", i, c);
		return -1;
	}
	else
		return n;
}

int main(){
	int i, c;
	i = 0;
	char input[MAX];
	printf("Enter Hex Number: ");
	while(i < MAX - 1 && (c = getchar()) != '\n' && c != EOF)
		input[i++] = c;
	input[i] = '\0';
	printf("Decimal equivalent: %ld\n", h2d(input));	
}
