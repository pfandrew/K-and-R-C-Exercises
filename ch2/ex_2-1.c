//compile: gcc ex_2-1.c
//run: ./a.out

//Exercise 2-1: Write a program to determine the ranges of char, short, int and long variables, both signed and unsigned, by printing appropriate values from standard headers and by direct computation. Harder if you compute them: determine the ranges of the various floating-point types.

//Note: This program just computes them. There are two ways to compute them: taking number of bits and converting max/min binary to decimal, or just counting. Both methods are employed.

unsigned long int power(int base, int exp){
	
	if(exp == 0)
		return 1;
	else
		return base*power(base, --exp);
}

#include <stdio.h>
int main(){
	signed char sc = 0;
	unsigned char usc = 0;
	signed short ss = 0;
	unsigned short uss = 0;
	signed long sl = 0;
	unsigned long usl = 0;
	signed int si = 0;
	unsigned int usi = 0;
	float f = 0.0;
	double d = 0.0;
	long double ud = 0.0;

	unsigned long long int low, high, i;
	

	//Unsigned Char - counting
	usc = 1;
	while(usc > 0)
		high = usc++;
	printf("Unsigned Char:  %lld <= X <=  %lld\n", 0, high);

	
	//Signed Char - counting
	sc = 1;
	while(sc > 0)
		high = sc++;
	sc = -1;
	while(sc < 0)
		low = sc--;
	
	printf("Signed Char:  %lld <= X <=  %lld\n", low, high);


	//Unsigned Short - computation from binary
	short bits = sizeof(uss)*8;
	low = high = 0;
	for(i = 0; i < bits; i++)
		high += power(2, i);
	printf("Unsigned Short:  %lld <= X <=  %lld\n", low, high);
	
	
	//Signed Short - computation.
	bits = sizeof(ss)*8;
	low = (signed short)power(2, bits - 1);
	high = 0;
	for(i = 0; i < bits - 1; i++)
		high += power(2, i);
	
	printf("Signed Short:  %lld <= X <=  %lld\n", low, high);


	//Unsigned Int - computation
	bits = sizeof(usi)*8;
	low = high = 0;
	for(i = 0; i < bits; i++)
		high += power(2, i);
	printf("Unsigned Int:  %lld <= X <=  %lld\n", low, high);

	
	//Signed Int - computation
	bits = sizeof(si)*8;
	high = 0;
	low = (signed int)power(2, bits - 1); 
	for(i = 0; i < bits - 1; i++)
		high += power(2, i);

	printf("Signed Int:  %lld <= X <=  %lld\n", low, high);


	//Unsigned Long - computation. Here, the long long int variable 'high' of 64 bits cannot help us, so we must use an unsigned 64 bit variable 'ul_high'.
	bits = sizeof(usl)*8;
	unsigned long ul_high = 0;
	low = 0;
	for(i = 0; i < bits; i++)
		ul_high += power(2, i);	
	printf("Unsigned Long:  %lld <= X <=  %llu\n", low, ul_high);


	//Signed Long - computation	
	bits = sizeof(sl)*8;
	low = (signed long)power(2, bits - 1);
	high = 0;
	for(i = 0; i < bits - 1; i++)
		high += power(2, i);

	printf("Signed Long:  %lld <= X <=  %lld\n", low, high);
	
	//due to strange weirdness, I was not able to manually convert binary into floating point. for instance, sizeof(float) gives 4 bytes, yet strangely a variable such as "float f" could store 8 bytes! And it did not seem to have: 1) a sign bit, 2) an exponent bit string or 3) a significand bit string. No manipulations to the string could result in a negative floating point number on my machine, or a change in the point position. In other words, float f = 0b11111111111111111111111111111111111111111111111111111111111111 (64 bits) simply out puts a 64 bit number. Will update this exercise as I learn more about floating point computation on my computer.
}
