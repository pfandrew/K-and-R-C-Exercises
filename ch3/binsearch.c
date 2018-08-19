//Example from 3.3; binary search algorithm implementation

#include <stdio.h>

int binsearch(int x, int v[], int n){
	int low, high, mid;
	low = 0;
	high = n-1;
	while(low <= high){
		mid = (low+high)/2;
		if(x < v[mid])
			high = mid -1;
		else if (x > v[mid])
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}

int main(){
	int arr[10] = {1,1,3,4,5,5,6,7,9,10};

	printf("In: %d, Match: at %d\n", 1, binsearch(1,arr,10));
}
