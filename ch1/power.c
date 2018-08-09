//Program from 1.7; function raises an integer m to nth power

#include <stdio.h>

int power(int m, int n);

int main(){
	int i;
	for(i = 0; i < 10; ++i)
		printf("%d %d %d\n", i, power(2,i), power(-3, i));
	return 0;
}

int power(int m, int n){
	int i, p;
	p = 1;
	
	for(i = 1; i <= n; ++i)
		p = p * m;
	
	return p;
}
