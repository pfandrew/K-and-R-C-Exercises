//compile: gcc ex_7-9.c -o implem
//compile: gcc ex_7-9.c -o stdlib
//run: time ./implem
//run: time ./stdlib

//Exercise 7-9: Functions like isupper can be implemented to save space or to save time. Explore both possibilities.

//Note - this is the only chapter in the book with an odd number of exercises :(

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define CHARS 1000000 /*at this size, the stdlib version of tolower() reported a millisecond faster speed*/

int to_lower(int c){
	if(c <= 90 && c >= 65)
		c += 32;
	return c;
}

int main(int argc, char *argv[]){
	
	char test[CHARS];
	int i;
	for(i = 0; i < CHARS; i++)
		test[i] = (i % 26) + 97;
	int (*fn)(int);
	if(strcmp(argv[0], "./implem"))
		fn = &to_lower;
	else
		fn = &tolower;

	for(i = 0; i < CHARS; i++)
	{
		test[i] = (*fn)(test[i]);
	}
	return 0;
}
