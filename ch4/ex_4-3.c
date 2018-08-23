//compile: gcc ex_4-3.c
//run: ./a.out

//Exercise 4-3: Given the basic framework, it's straightforward to extend the calculator. Add the modulus (%) operator and provisions for negative numbers.

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
void clear_stack();


int sp = 0;
double val[MAXVAL];
char buf[BUFSIZE];
int bufp = 0;
int tmp = 0;

short curr_ops = 0;

int main(){
	int type;
	double op1, op2;
	int i_op1, i_op2;
	char s[MAXOP];

	while((type = getop(s)) != EOF){
		switch(type){
		case NUMBER:
			curr_ops++;
			push(atof(s));
			break;
		case '+':
			push(pop() + pop());
			curr_ops = 0;
			break;
		case '*':
			push(pop() * pop());
			curr_ops = 0;
			break;
		case '-':
			op2 = pop();
			push(pop() - op2);
			curr_ops = 0;
			break;
		case '/':
			op2 = pop();
			if(op2 != 0.0){
				push(pop() / op2);
				curr_ops = 0;
			}
			else
				printf("error: zero divisor\n");
			break;
		case '%':
			op2 = pop();
			if(op2 != 0.0){
				push((int)pop() % (int)op2);
				curr_ops = 0;
			}
			else
				printf("error: n mod 0 is undefined\n");
			break;
		case '\n':
			printf("\t%.8f\n", pop());
			break;
		case 'd': // duplicate it
			tmp = 0;
			printf("Stack: ");
			while(tmp < sp)
				printf("%f ", val[tmp++]);
			printf("\n");
			break;
		case 'c': //clear stack
			while(sp > 0)
				pop();
			push(0.0);
			break;
		case 'p': //print top of stack
			if(sp > 0)
				printf("Top of stack: %f\n", val[sp - 1]);
			else
				push(0.0);
			break;
		case 's': //swap top two elements
			if(sp >= 2)
			{
				op1 = pop();
				op2 = pop();
				push(op1);
				push(op2);
			}
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
	int i, c, sign = 1;

	while((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if(!isdigit(c) && c != '.' && c != '-')
		return c;
	if(c == '-' && curr_ops  == 2)
		return c;
	if(isdigit(c) || c == '-')
		while(isdigit(s[++i] = c = getch()))
			;
	if(c == '.')
		while(isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if(c != EOF)
		ungetch(c);
	return NUMBER;
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
