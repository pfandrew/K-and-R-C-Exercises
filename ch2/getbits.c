//function from section 2.9; getbits(x, 4, 3) returns three bits towards the right beginning at position 4 (eg, getbits(0b1001001, 4, 3) = 0b010)
#include <stdio.h>

unsigned getbits(unsigned x, int p, int n){
	return (x >> (p + 1 - n)) & ~(~0 << n);
}

int main(){
	printf("getbits(%d, 4, 3) = %u\n", 0b1001001, getbits(0b1001001, 4, 3));
	return 0;
}


