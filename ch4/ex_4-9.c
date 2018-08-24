//compile: gcc ex_4-9.c
//run: ./a.out

//Exercise 4-9: Our getch and ungetch do not handle a pushed-back EOF correctly. Decide what their properties ought to be if EOF is pushed back, then implement your design.

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
			printf("error: unknown command %s\n", s);
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
	int i, c;

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
	ungetch(c);
	return NUMBER;
}

//if EOF is pushed onto the buffer by getop, which is not possible in the current program
//ungetch should not allow anything else to be pushed on it. 
//When getch eventually asks for character input
//it will pass the EOF to getops, which will pass it back to main after isdigit(EOF) fails
//which will terminate the loop.
//now we don't need to test for c != EOF in getop.
int getch(void){
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c){
	if(bufp >= BUFSIZE && c != EOF)
		printf("ungetch: too many characters\n");
	else if(buf[0] == EOF) //don't allow new input into the buffer
		return;
	else if(c == EOF){ //clear buffer, add EOF
		bufp = 0;
		buf[bufp++] = c;
		return;
	}
	else //store character
		buf[bufp++] = c;
}
