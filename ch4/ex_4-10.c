//compile: gcc ex_4-10.c
//run: ./a.out

//Exercise 4-10: An alternate organization uses getline to read an entire input line; this makes getch and ungetch unnecessary. Revise the calculator to use this approach.


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINE 100
#define NUMBER '0'
#define MAXVAL 100
#define BUFSIZE 100
#define TRUE 1
#define FALSE 0

int getop(char [], char[], int);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);
int get_line(char [], int);

int sp = 0;
double val[MAXVAL];
char buf[BUFSIZE];
int bufp = 0;
int loc = 0;

int main(){
	int type, i, len, parsing = TRUE;
	double op2;
	char s[MAXLINE];
	char t[MAXLINE];
	while((len = get_line(s, MAXLINE)) > 0 && parsing){
		loc = 0;
		while(loc < len){
			switch((type = getop(s, t, loc))){
				case NUMBER:
					push(atof(t));
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
				case EOF:
					parsing = FALSE;
					i = len;
					break;
				case '\0':
					loc = len;
					break;
				default:
					printf("error: unknown command %s\n", s);
					break;
			}
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

int getop(char s[],  char t[], int index){
	int i, c;
	i = 0;
	//remove whitespace
	while((t[0] = c = s[index]) == ' ' || c == '\t')
		index++;
	t[1] = '\0';
	if(!isdigit(c) && c != '.'){
		loc = ++index;
		return c; //EOF, '\n', et al
	}
	if(isdigit(c))
		while(isdigit(t[++i] = c = s[++index]))
			;
	if(c == '.')
		while(isdigit(t[++i] = s[++index]))
			;
	loc = index;
	t[i] = '\0'; 
	return NUMBER;
}

int get_line(char s[], int lim){
	int c, i;
	for(i = 0; i < lim - 1 && (c = getchar()) != '\n'; ++i)
		s[i] = c;
	if(c == '\n'){
		s[i++] = c;
	}
	s[i] = '\0';
	return i;
}
