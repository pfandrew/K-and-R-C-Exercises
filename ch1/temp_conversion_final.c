//compile: gcc temp_conversion_final.c
//run: ./a.out

//Final version of temperature conversion program from chapter 1. Uses all language features taught up to section 1.4

#include <stdio.h>
#define	LOWER	0
#define	UPPER	300
#define	STEP	20

int main(){
	int fahr;
	printf("---------------\nFahr.\t Cels.\n---------------\n");
	for(fahr = LOWER; fahr <= UPPER; fahr = fahr + STEP)
		printf("%3d\t%6.1f\n",fahr, (5.0/9.0)*(fahr - 32));
}
