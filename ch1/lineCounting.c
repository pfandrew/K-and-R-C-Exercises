//1.5.3 Example program; counts the number of lines in input.

#include <stdio.h>

int main(){
	int c, n1;
	n1 = 0;
	while((c = getchar()) != EOF)
		if(c == '\n')
			++n1;

	printf("%d\n", n1);
}
