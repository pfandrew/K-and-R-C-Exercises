//compile: gcc ex_3-4.c
//run: ./a.out

//Exercise 3-4: In a two's complement number representation, our version of itoa does not handle the largest negative number, that is, the value of n equal to -(2^(wordsize-1)). Explain why not. Modify it to print that value correctly, regardless of the machine on which it runs.

/*Explanation: In a two's complement number representation system, the leftmost bit of the word is 1 if the number is negative, and 0 if it is positive. Additionally, it is designed such that when negative numbers are added to positive numbers of the same magnitude, the binary representations of those numbers have a single overflow 1-bit, with the rest of the original bits being 0. For instance, if there are three bits:

	101 (-3) + 011 (3) = 1000, 

where the left most 1 is considered overflow, since we are only dealing with three bits. This way, we can represent signed numbers and perform addition and subtraction with the same rules as unsigned arithmetic.

If we are dealing with a word size of 32, then the largest negative number is -(2^(wordsize - 1)) (just as if the word size is three, then then largest negative number we can consider is, represented in two's complement, 100.

Because the largest positive number is (2^(wordsize - 1) - 1)), there is no positive representable with wordsize bits that can sum with the largest negative to create 0. For instance, with three bits, the largest negative is -4 or -(2^(wordsize-1)), where wordsize is 3. The largest positive is 3, or (2^(wordsize-1) - 1). 

The original itoa function operates by turning every negative number into a positive number. Since in a 2's complement system, the largest negative has no positive representable counterpart with the same number of bits, it inverts all the bits of the largest negative and adds 1, resulting in itself. This causes each iteration of the do while loop which does not result in 0, to result in a negative numer, a critical error when indexing an array, resulting in undefined behavior. 

*/	

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

void itoa(int n, char s[]){
	int i; 
	int sign;

	if(n < 0)
		sign = NEG;
	else
		sign = POS;

	i = 0;
	
	do {
		s[i++] = sign*(n % (sign*10)) + '0';
	} while ((n /= 10) != 0);
	
	if(!(sign + 1))
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

int main(){
	char num[MAX];
	
	itoa(-2147483648, num);
	printf("%s\n", num);
}
