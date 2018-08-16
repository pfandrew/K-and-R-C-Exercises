//Functions are from section 2.7; rand calculates a 'random' number from the seed; srand seeds the next random number

#include <stdio.h>

unsigned long int next = 1;

int rand(void){
	next = next * 1103515245 + 12345;
	return (unsigned int)(next/65536) % 32768;
}

void srand(unsigned int seed){
	next = seed;
}

int main(){

	printf("Pseudo-random number with seed %lu: %d\n", next, rand());
	srand(5);
	printf("Pseudo-random number with seed %lu: %d\n", next, rand());
	return 0;
}
