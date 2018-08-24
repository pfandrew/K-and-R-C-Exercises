//qsort implementation from section 4.10; uses recursion
//if you're not familiar with qsort, reading this helps: https://en.wikipedia.org/wiki/Quicksort
#include <stdio.h>
void qsort(int v[], int left, int right){
	int i, last;
	void swap(int v[], int i, int j);
	if(left >= right)
		return;
	swap(v, left, (left + right)/2);
	last = left;
	for(i = left + 1; i <= right; i++){
		if(v[i] < v[left])
			swap(v, ++last, i);
	}
	swap(v, left, last);
	qsort(v, left, last-1);
	qsort(v, last + 1, right);
}

void swap(int v[], int i, int j){
	int tmp = v[i];
	v[i] = v[j];
	v[j] = tmp;
}

int main(){
	int unsorted[6] = {1,9,3,2,7,6};
	qsort(unsorted, 0, 5);
	for(int i = 0; i < 6; i++)
		printf(" %d", unsorted[i]);
}
