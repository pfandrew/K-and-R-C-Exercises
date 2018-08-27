//example from 5.8; given an integer n, returns the month name
#include <stdio.h>
char *month_name(int n){
	static char *name[] = {
		"Illegal Month",
		"January",
		"February",
		"March",
		"April",
		"May",
		"June",
		"July",
		"August",
		"September",
		"October",
		"November",
		"December"
	};

	return (n < 1 || n > 12) ? name[0] : name[n];
}

int main(){
	printf("Month %d: %s\n", 5, month_name(5));
}
