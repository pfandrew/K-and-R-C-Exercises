//compile: gcc ex_5-2.c
//run: ./a.out

//Exercise 5-2: Write getfloat, the floating-point analog of getint. What type does getfloat return as its function value?

#include <stdio.h>
#include <ctype.h>

#define MAXVAL 100
#define BUFSIZE 100

int getch(void);
void ungetch(int);
int get_double(double *dn);

int sp = 0;
double val[MAXVAL];
char buf[BUFSIZE];
int bufp = 0;

int get_double(double *dn){
	int c;
	double sign, power = 1;
	while(isspace(c = getch()))
		;
	if(!isdigit(c) && c != EOF && c != '=' && c != '-' && c != '+' && c != '.'){
		ungetch(c);
		return 0.0;
	}
	sign = (c == '-') ? -1.0 : 1.0;
	if(c == '+' || c == '-')
		c = getch();
	for(*dn = 0; isdigit(c); c = getch())
		*dn = 10.0 * *dn + (c - '0');
	if(c == '.'){
		while(isdigit(c = getch())){
			*dn = 10.0 * *dn + (c - '0');
			power *= 10.0;
		}
	}
	if (c != EOF)
		ungetch(c);
	*dn *= (sign/power);
	return c;
}

int main(){
	int c, k = 0;
	double i = 0.0;
	double nums[MAXVAL];
	while((c = get_double(&i)) > 0.0 && c != EOF){
		nums[k++] = i;
	}
	printf("You entered: ");
	for(c = 0; c < k; c++){
		printf(" %f", nums[c]);
	}
	printf("\n");
}

int getch(void){
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c){
	if(bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}
