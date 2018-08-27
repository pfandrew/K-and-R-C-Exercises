//compile: gcc ex_5-10.c
//run: ./a.out

//Exercise 5-10: Write the program expr, which evaluates a reverse Polish expression from the command line, where each operator or operand is a seperated argument.
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define STACK_MAX 100
#define NUMBER 'n'

static double stack[STACK_MAX];
static int stack_index = 0;

void push(double);
double pop(void);
double atof(char*);

int main(int argc, char *argv[]){
	double op1, op2;
	int parsing = 1, c, isd;
	char* s;
	while(--argc > 0 && *++argv){
		parsing = 1;
		while((c = *(*argv)++) != '\0' && parsing){
			isd = isdigit(c);
			if(isd) c = NUMBER;
			switch(c){
				case NUMBER:
					push(atof(--(*argv))); parsing = 0; break;
				case '+':
					op1 = pop();
					op2 = pop();
					push(op1 + op2); break;
				case '-':
					if(strlen(--*argv) > 1 && isdigit(*++*argv)){
						push(atof(--*argv));
						parsing = 0;
					}
					else{
						op2 = pop();
						push(pop() - op2);
					}
					break;
				case '/':
					op2 = pop();
					if(op2 == 0.0){
						printf("no division by 0\n");
						argc = 0;
						parsing = 0;
					}
					else{
						push(pop()/op2);
					}
					break;
				case '*':
					push(pop()*pop());
					break;
				default:
					printf("Unrecognized operator/operand %s\n", *argv);
					argc = 0;
					parsing = 0;
					break;
			}
		}
	}
	printf("\t%f\n", pop());
}

double atof(char *s){
	double val, power;
	int i, sign;
	for(i = 0; isspace(*s); s++)
		;
	sign = *s == '-' ? -1 : 1;
	if(*s == '+' || *s == '-')
		s++;

	for(val = 0.0; isdigit(*s); s++)
		val = 10.0 * val + (*s - '0');
	if(*s == '.')
		s++;
	for(power = 1.0; isdigit(*s); s++){
		val = 10.0 * val + (*s - '0');
		power = power * 10.0;
	}

	return sign * val / power;
}

void push(double val){
	if(stack_index < STACK_MAX)
		stack[stack_index++] = val;
	else
		printf("error: stack full\n");
}
double pop(void){
	double val;
	if(stack_index > 0){
		val = stack[--stack_index];
		return val;
	}
	else{
		printf("error: stack empty\n");
		return -1;
	}
}

