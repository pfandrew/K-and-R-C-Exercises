//compile: gcc ex_5-1.c
//run: ./a.out

//Exercise 5-1: As written, getint treats a + or - not followed by a digit as a valid representation of zero. Fix it to push such a character back on the input.

//NOTE: I *believe* the exercise is asking you to push back the sign, and not the space between the sign and the next number.
//Ultimately, I'm not sure what it is asking you to do. So I pushed back the sign and reorganized the program such that the
//sign followed by a white space applies to the next number.

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


int main(){
	int c, k = 0;
	int nums[MAXVAL];
	while((c = get_int(&nums[k++])) != 'e')
		k = (k > 0) ? k + c : 0;
	printf("You entered: ");
	for(c = 0; c < k - 1; c++){
		printf(" %d", nums[c]);
	}
	printf("\n");
}

int get_int(int *pn){
	int c, d, sign;
	while(isspace(c = getch()))
		;
	if(!isdigit(c) && c != EOF && c != '+' && c != '-'){
		ungetch(c);
		return -1;
	}
	sign = (c == '-') ? -1 : 1;
	
	if(c == '+' || c == '-'){
		d = c;
		c = getch();
		if(!isdigit(c)){
			ungetch(d); return (c == EOF) ? 'e' : -1;
		} 
	}
		
	for(*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if(c != EOF)
		ungetch(c);
	else
		return 'e';
	return 0;
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

