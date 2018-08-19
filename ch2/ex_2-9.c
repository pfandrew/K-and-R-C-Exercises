//compile: gcc ex_2-9.c
//run: ./a.out

//Exercise 2-9: In a two's complement number system, x &= (x-1) deletes the rightmost 1-bit in x. Explain why. Use this observation to write a faster version of bitcount.

/*
	Case 1a) If the bit string has length = 1, then it is possible to not have a 1-bit:
 
		x = 0 & (-1), 
	
	Even if some 0-bits in 0 are turned into 1 with the subtraction, all 1 bits in -1 will be ANDed with 0-bits in 0, and the result will be 0.

	Case 1b) If the bit string has length = 1, and has a 1 bit, then this is equivalent to:		

		x = 1 & (0)

	Which by definition will be 0, deleting the rightmost 1 bit.

	Case 2) If the bit string is length > 1, and has a 1-bit as it's right-most bit, then the above holds as well, and only the right-most one-bit is deleted.

		10000001101101 (x)
	  	 -	     1
		--------------
		10000001101100 (x - 1)


		10000001101101  (x)
	       &10000001101100  (x - 1)
		--------------
	    	10000001101100  (x & (x - 1))
		.
	Case 3) If the bit string is any length > 1, and doesn't have a 1-bit as its right-most bit, then it still must have a right-most 1-bit, even if it is the leftmost bit. If we take any bit-string and subtract 1, then the resulting number will be 1 less than the original, meaning the rightmost bit in x, even if it is the left-most bit,  must be converted to a 0, and all following 0s to the right of it must be converted to 1s:

	11001000 (x)
   	-      1
    	--------
	11000111 (x - 1)
            ^--^
	     ||
          inverted

	Since the rightmost 1-bit in x is now a 0-bit in (x-1), and, since all 0-bits following the right-most bit in x towards the right, are now 1-bits in x-1, ANDind these two strings results in, starting at the position of the right-most 1-bit in x, everything at the location of the rightmost 1-bit in x and following it, towards the right, being 0. But it doesn't affect any bits to the left of the right-most 1-bit in x, which are the same as in x-1 at the same locations.

	11001000 (x)
       &11000111 (x - 1)
    	--------
    	11000000 (x & (x-1))


Whether the number is positive or negative is irrelevant, since the operators work on raw bit strings, not the numbers they represent.

Therefore, with (x & (x-1)), either 0 bits will be deleted if the number is 0, or only the rightmost bit in the bit-string will be deleted if x is greater than 0.*/

#include <stdio.h>

int bitcount(unsigned x){
	int b = 0;
	while(x > 0){
		x &= (x-1);
		b++;
	}
	return b;
}

int main(){
	printf("1-bits in '%d': %u\n", 0, bitcount(0));
	printf("1-bits in '%d': %u\n", 0b10000000, bitcount(0b10000000));	
	printf("1-bits in '%d': %u\n", 0b110110001101101100111, bitcount(0b110110001101101100111));
}
