//example from section 5.2; uses a pointer to return an int from input stream
#include <stdio.h>
#include <ctype.h>

#define MAXVAL 100
#define BUFSIZE 100

int getch(void);
void ungetch(int);
int get_int(int *pn);

int sp = 0;
double val[MAXVAL];
char buf[BUFSIZE];
int bufp = 0;

int get_int(int *pn){
	int c, sign;
	while(isspace(c = getch()))
		;
	if(!isdigit(c) && c != EOF && c != '=' && c != '-'){
		ungetch(c);
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if(c == '+' || c == '-')
		c = getch();
	for(*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if(c != EOF)
		ungetch(c);
	return c;
}

int main(){
	int c, i = 0, k = 0;
	int nums[MAXVAL];
	while((c = get_int(&i)) > 0 && c != EOF){
		nums[k++] = i;
	}
	printf("You entered: ");
	for(i = 0; i < k; i++){
		printf(" %d", nums[i]);
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
