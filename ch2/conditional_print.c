//Examples from section 2.11; 
//first uses a conditional in a print statement to print 10 elements of an array per line
//second conditionally prints an 's' to the end of term, depending on the number of items

#include <stdio.h>
#define MAX 25
int main(){
	int i, items;
	i = items = 0;
	int nums[MAX];
	for(i = 0; i < 25; i++)
		nums[i] = i;

	for(i = 0; i < MAX; i++)
		printf("%6d%c", nums[i], (i%10==9 || i == MAX-1) ? '\n' : ' ');

	items = 1;
	printf("\nYou have %d item%s\n", items, items == 1 ? "" : "s");

	return 0;
}
