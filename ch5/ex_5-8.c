//compile: gcc ex_5-8.c
//run: ./a.out

//Exercise 5-8: There is no error checking in day_of_year or month_day. Remedy this defect.

#include <stdio.h>
static char daytab[2][13] = {
	{0,31,28,31,30,31,30,31,31,30,31,30,31},
	{0,31,29,31,30,31,30,31,31,30,31,30,31}	
};


int day_of_year(int year, int month, int day){
	int i, leap;
	if(year < 0){
		printf("Sorry, AD only\n");
		return 0;
	}
	else if(month < 0 || month >= 12){
		printf("Month must be between 1 and 12\n");
		return 0;
	}
	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
	if(day > daytab[leap][month]){
		printf("There aren't %d days in month %d of %d!\n", day, month, year);
		return 0;
	}

	for(i = 1; i < month; i++)
		day += daytab[leap][i];
	return day;
}

int month_day(int year, int yearday, int *pmonth, int *pday){
	int i, leap;
	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
	if(yearday > 365 + leap || yearday < 1){
		printf("Sorry, there is no day no. %d in year %d\n", yearday, year);
		return 0;
	}
	for(i = 1; yearday > daytab[leap][i]; i++)
		yearday -= daytab[leap][i];
	*pmonth = i;
	*pday = yearday;
	return 1;
}

int main(){

	//testing month_day
	int month;
	int day;
	int year = 2004;
	int yearday = 367;
	int r = month_day(year, yearday, &month, &day);
	if(r)
		printf("Day %d of %d: %d/%d/%d\n", yearday, year, month, day, year);

	//testing day_of_year
	month = 8;
	day = 6;
	year = -1;
	r = day_of_year(year, month, day);
	if(r)
		printf("%d/%d/%d was day %d of %d\n", month, day, year, r, year);
	return 0;
}
