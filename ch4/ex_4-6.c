//compile: gcc ex_4-6.c
//run: ./a.out

//Exercise 4-6: Add commands for handling variables. (It's easy to provide twenty-six variables with single-letter names.) 
//Add a variable for the most recently printed value.

/*NOTE: you can define a variable with "define [var_name] [double]", where var_name has to be a single letter, 
and double has to be an integral value. You can print a variables value with "print [var_name]", 
where var_name must be defined already, and must be a single letter. You can also use previously defined values with 
operands, such as "x y +. However, definitions cannot be made in terms of the results of other operations, for instance 
"define x y z +", which defines x as y + z.
finally, "last" is parsed as a function by the program, but does push(last) so it can be used in operations such as "last 8 +"
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define MAXOP 100
#define NUMBER '0'
#define MAXVAL 100
#define BUFSIZE 100
#define NUMFUNCS 14
#define NO_FUNC -1
#define FUNCTION 'f'
#define MAXVARS 52
#define VARIABLE 'v'

int getop(char []);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);
void run_func(int);
int cmp_func(char []);
int isvar(int);
double var_value(int);


int sp = 0;
double val[MAXVAL];
char buf[BUFSIZE];
int bufp = 0;
int tmp = 0;
char* funcs[NUMFUNCS] = {"sin", "cos", "tan", "exp", "log", "pow", "sqrt", "swap", "duplicate", "clear", "print_top", "define", "print", "last"};
double vars[MAXVARS];
short defined[MAXVARS];
short curr_ops = 0;
double last;

int main(){
	int type;
	double op1, op2;
	int i_op1, i_op2, i = 0, d;
	char s[MAXOP];

	for(int k = 0; k < MAXVARS; k++)
		defined[k] = 0;

	while((type = getop(s)) != EOF){
		switch(type){
		case NUMBER:
			curr_ops++;
			push(atof(s));
			break;
		case VARIABLE:
			curr_ops++;
			push(var_value(s[0]));
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
			last = pop();
			printf("\t%.8f\n", last);
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

//looks through list of functions for whether or not input matches
int cmp_func(char f[]){
	int i, k;;
	for(i = 0; i < NUMFUNCS; i++){
		for(k = 0; f[k] == funcs[i][k] && f[k] != '\0'; k++)
			;
		if(f[k] == '\0' && funcs[i][k] == '\0'){ //found the function	
			return i;
		}
	}
	return NO_FUNC;
}

//switch cases ref: char* funcs[] = {"sin", "cos", "tan", "exp", "log", "pow", "sqrt", "swap", "duplicate", "clear", "print_top", "define", "print"};
void run_func(int i){
	double op1, op2;
	int tmp = 0, upper, lower, c, k = 0;
	char num_arr[MAXVAL];
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
				printf("Stack empty");
			if((c = getch()) != '\n')
				ungetch(c);	
			break;
		//assignment grammar: [define] [var] [value]
		//var must be a single character
		//value must be integral
		case 11:
			while(isspace(c = getch()))
				;
			tmp = c;
			if(!((upper = tmp >= 'A' && tmp <= 'Z') || (lower = tmp >= 'a' && tmp <= 'z'))){
				printf("error: variable name must be a single letter, upper or lower case\n");
				tmp = -1;
			}
			while(isspace(c = getch()))
				;
			if(!isdigit(c))
				printf("error: value for variable must be integral\n");	
			else{
				//handle floats for variable
				num_arr[k++] = c;
				while(isdigit(c = getch()))
					num_arr[k++] = c;
				if(c != EOF)
					ungetch(c);

				if((c = getch()) ==  '.')
					num_arr[k++] = c;
				else
					ungetch(c);
				while(isdigit(c = getch()))
					num_arr[k++] = c;
				if(c != EOF)
					ungetch(c);
				num_arr[k] = '\0';
				op1 = atof(num_arr);
			}
			if(tmp == -1)
				break;
			else if(upper){
				vars[tmp - 'A' + 26] = op1;
				defined[tmp - 'A' + 26] = 1;
			}
			else if(lower){
				vars[tmp - 'a'] = op1;
				defined[tmp - 'a'] = 1;
			}
			if((c = getch()) != '\n')
				ungetch(c);	
			break;
		//print grammar: print [var_name] = [val]
		case 12: 
			while(isspace(c = getch()))
				;
			if(!((upper = c <= 'Z' && c >= 'A')||(lower = c <= 'z' && c >= 'a')))
				printf("error: variable name must be a single letter, upper or lower case\n");
			else
				printf("%c = %f\n", c, upper ? vars[c - 'A' + 26]: vars[c - 'a']);
			//prevent newline from popping
			if((c = getch()) != '\n')
				ungetch(c);
			break;
		case 13:
			push(last);
			curr_ops++;
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
		return 0.0;
	}
}

int isvar(int c){
	int upper, lower, j;
	if(((upper = c >= 'A' && c <= 'Z') || (lower = c >= 'a' && c <= 'z')) && isspace(j = getch()))
		return defined[upper?c-'A'+26:c-'a'];
	else
		ungetch(j);
	return 0;
}

double var_value(int c){
	return vars[isupper(c)?c-'A'+26:c-'a'];
}

int getop(char s[]){
	int i = 0, c, sign = 1, func = 0, sb = 0, sa = 0;

	while((s[0] = c = getch()) == ' ' || c == '\t')
		sb++;
	s[1] = '\0';
	//check if any other chars we need to lookk for are input first	
	//variables are the lone appearance of any character, upper or lower casei
	/*if(isvar(c)){
		return VARIABLE; 
	}
	*/
	if(c == '+' || c == '/' || c == '*' || c == '%' || c == '\n' || c == EOF)
		return c;
	//handle minus as binary operator
	else if(c == '-' && curr_ops  == 2)
		return c;
	//handle character strings - functions and assignments
	else if(!isdigit(c) && c != '.' && c != '-')
	{
		while(!isdigit(s[++i] = c = getch()) && !isspace(c) && c != EOF)
			;
		s[i] = '\0';
		if(c != EOF)
			ungetch(c);
		if(isvar(s[0])) 
				return VARIABLE;
		else
			return FUNCTION;
	}
	//handle numbers
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
