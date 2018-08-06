//compile: gcc ex_1-5.c
//run: ./a.out

//Exercise 1-5: Modify the temperature conversion program to print the table in reverse order, that is, from 300 degrees to 0.

#include <stdio.h>

int main(){
	printf("---------------\nFahr.\t Cels.\n---------------\n");
	int fahr;
	for(fahr = 300; fahr >= 0; fahr = fahr - 20)
		printf("%3d\t%6.1f\n", fahr, (5.0/9.0)*(fahr - 32));
}
