//compile: gcc ex_4-5.c
//run: ./a.out

//Exercise 4-5: Add access to library functions like sin, exp and pow. See <math.h> in Appendix B, Section 4.

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define MAXOP 100
#define NUMBER '0'
#define MAXVAL 100
#define BUFSIZE 100
#define NUMFUNCS 11
#define NO_FUNC -1
#define FUNCTION 'f'

int getop(char []);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);
void run_func(int);
int cmp_func(char []);


int sp = 0;
double val[MAXVAL];
char buf[BUFSIZE];
int bufp = 0;
int tmp = 0;
char* funcs[] = {"sin", "cos", "tan", "exp", "log", "pow", "sqrt", "swap", "duplicate", "clear", "print_top"};

short curr_ops = 0;

int main(){
	int type;
	double op1, op2;
	int i_op1, i_op2, i = 0, d;
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
		case FUNCTION:
			if((d = cmp_func(s)) >= 0)
				run_func(d);
			else{
				printf("Unrecognized function '%s'\n", s);
			}
			break;	
		default:
			printf("error: unknown command %s\n", s);
			break;
		}
	}
	return 0;
}

int cmp_func(char f[]){
	int i, k, f_i = -1;
	//look through list of functions for whether or not input matches
	for(i = 0; i < NUMFUNCS; i++){
		for(k = 0; f[k] == funcs[i][k] && f[k] != '\0'; k++)
			;
		if(f[k] == '\0' && funcs[i][k] == '\0'){ //found the function	
			return i;
		}
	}
	return NO_FUNC;
}

//char* funcs[] = {"sin", "cos", "tan", "exp", "log", "pow", "sqrt", "swap", "duplicate", "clear", "print_top"};
void run_func(int i){
	double op1, op2;
	int tmp = 0;
	switch(i){
		case 0: push(sin(pop())); break;
		case 1: push(cos(pop())); break;
		case 2: push(tan(pop())); break;
		case 3: push(exp(pop())); break;
		case 4: push(log(pop())); break;
		case 5: op2 = pop(); push(pow(pop(), op2)); break;
		case 6: op1 = pop(); op1 >= 0.0 ? push(sqrt(op1)) : printf("error: negative roots undefined.\n"); break;
		case 7:
			if(sp >= 2)
			{
				op1 = pop();
				op2 = pop();
				push(op1);
				push(op2);
			}
			break;
		case 8:
			printf("Stack: ");
			while(tmp < sp)
				printf("%f ", val[tmp++]);
			printf("\n");
			break;
		case 9:
			while(sp > 0)
				pop();
			push(0.0);
			break;
		case 10:
			if(sp > 0)
				printf("Top of stack: %f\n", val[sp - 1]);
			else
				push(0.0);
			break;
		default: printf("function not found\n");
			break;
	}
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
	int i = 0, c, sign = 1, func = 0;

	while((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	
	if(c == '+' || c == '/' || c == '*' || c == '%' || c == '\n')
		return c;
	else if(c == '-' && curr_ops  == 2)
		return c;
	//character string - function etc.
	else if(!isdigit(c) && c != '.' && c != '-')
	{
		while(!isdigit(s[++i] = c = getch()) && !isspace(c) && c != EOF)
			;
		s[i] = '\0';
		if(c != EOF)
			ungetch(c);
		return FUNCTION;
	}
	//numbers
	else if(isdigit(c) || c == '-' || c == '.'){
		while(isdigit(s[++i] = c = getch()))
			;
		if(c == '.')
			while(isdigit(s[++i] = c = getch()))
				;
	}
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
