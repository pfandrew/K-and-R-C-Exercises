//compile: gcc ex_3-1.c
//run: time ./a.out

/*Exercise 3-1: Our binary search makes two tests inside the loop, when one would suffice (at the price of more tests outside).
Write a version with only one test inside the loop and measure the difference in run-time.*/

#include <stdio.h>

int binsearch(int x, int v[], int n){
	int low, high, mid;
	low = 0;
	high = n-1;
	while(low <= high){
		mid = (low + high)/2;
		if(x < v[mid])
			high = mid - 1;
		else
			low = mid + 1;	
	}
	if(v[low] == x || v[high] == x)
	{
		return (v[low] == x) ? low : high;
	}
	else
		return -1;
}

int main(){
	int arr[10] = {1,2,3,4,5,6,7,8,9,10};
	printf("%d at location %d\n", 5, binsearch(5, arr, 10));
}
