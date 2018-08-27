//compile: gcc ex_5-9.c
//run: ./a.out

//Exercise 5-9: Rewrite the routines day_of_year and month_day with pointers instead of indexing.

#include <stdio.h>
static char daytab[2][13] = {
	{0,31,28,31,30,31,30,31,31,30,31,30,31},
	{0,31,29,31,30,31,30,31,31,30,31,30,31}	
};

int day_of_year(int year, int month, int day){
	int i, leap;

	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
	for(i = 1; i < month; i++)
		day += *(*(daytab + leap) + i);
	return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday){
	int i, leap;
	
	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
	for(i = 1; yearday > *(*(daytab + leap) + i); i++)
		yearday -= *(*(daytab + leap) + i);
	*pmonth = i;
	*pday = yearday;
}

int main(){

	//testing month_day
	int month;
	int day;
	int year = 1998;
	int yearday = 105;
	month_day(1998, yearday, &month, &day);
	printf("Day %d of %d: %d/%d/%d\n", yearday, year, month, day, year);

	//testing day_of_year
	month = 8;
	day = 6;
	year = 1992;
	printf("%d/%d/%d was day %d of %d\n", month, day, year, day_of_year(year, month, day), year);
	return 0;
}
