//function from section 4.10; uses recursion to avoid having to reverse a string when converting integer to array of chars
#include <stdio.h>
void printd(int n){
	if(n < 0){
		putchar('-');
		n = -n;
	}
	if(n / 10)
		printd(n / 10);
	putchar(n % 10 + '0');
}

int main(){
	printd(8765);
}
