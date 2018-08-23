//compile: gcc ex_4-11.c
//run: ./a.out

//Exercise 4-11: Modify getop so that it doesn't need to use ungetch. Hint: use an internal static variable.

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP 100
#define NUMBER '0'
#define MAXVAL 100
#define BUFSIZE 100

int getop(char []);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);

int sp = 0;
double val[MAXVAL];
char buf[BUFSIZE];
int bufp = 0;

int main(){
	int type;
	double op2;
	char s[MAXOP];

	while((type = getop(s)) != EOF){
		switch(type){
		case NUMBER:
			push(atof(s));
			break;
		case '+':
			push(pop() + pop());
			break;
		case '*':
			push(pop() * pop());
			break;
		case '-':
			op2 = pop();
			push(pop() - op2);
			break;
		case '/':
			op2 = pop();
			if(op2 != 0.0)
				push(pop() / op2);
			else
				printf("error: zero divisor\n");
			break;
		case '\n':
			printf("\t%.8f\n", pop());
			break;
		default:
			printf("error: unknown command '%s\n'", s);
			break;
		}
	}
	return 0;
}

void push(double f){
	if(sp < MAXVAL)
		val[sp++] = f;
	else 
		printf("error: stack full, can't push %f\n", f);
}

double pop(void){
	if(sp > 0)
		return val[--sp];
	else{
		printf("error: stack empty\n");
		return 0.0;
	}
}

int getop(char s[]){
	int i, c = ' ';
	static char c_buf[BUFSIZE];
	static int i_buf = 0;
	//go thru buffer first for any non-space chars
	while(i_buf > 0 && ((s[0] = c = c_buf[--i_buf]) == ' ' || c == '\t'))
		;
	if(c == ' ' || c == '\t')
		while((s[0] = c = getch()) == ' ' || c == '\t')
			;
	s[1] = '\0';
	if(!isdigit(c) && c != '.')
		return c;
	if(isdigit(c))
		while(isdigit(s[++i] = c = getch()))
			;
	if(c == '.')
		while(isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if(c != EOF)
	{
		if(i_buf == BUFSIZE)
			printf("error: too many chars in buffer\n");
		else
			c_buf[i_buf++] = c;
	}
	printf("C: %c\n", c);
	return NUMBER;
}

int getch(void){
	return (bufp > 0) ? buf[--bufp] : getchar();
}
