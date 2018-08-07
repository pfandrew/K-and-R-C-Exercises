//compile: gcc ex_1-6.c
//run: ./a.out 

//Exercise 1-6: Verify that the expression getchar() != EOF is 0 or 1.

#include <stdio.h>

int main(){

	int c;
	
	while(c = (getchar() != EOF))
		printf("(getchar() != EOF) == %d\n", c);

	//after EOF detected
	printf("(getchar() == EOF) == %d", c);	
}
