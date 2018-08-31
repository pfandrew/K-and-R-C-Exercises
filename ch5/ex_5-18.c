//compile: gcc ex_5-18.c -o ex518
//run: ./ex518

//Exercise 5-18: Make dcl recover from input errors.

/*
	errors solved:
		spurious blank in between parentheses leading to error:
			int x( )
		invalid entries muck up the next entry, even if it is properly entered. 
			ERROR type introduced to make sure program stops processing when dirdcl sets tokentype to ERROR
			and clears everything out to restart.
		
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define BUFSIZE 100


enum { NAME, PARENS, BRACKETS, ERROR };

void dcl(void);
void dirdcl(void);
int gettoken(void);
int getch(void);
void ungetch(int);

int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];
char buf[BUFSIZE];
int bufp = 0;

/*dcl*/
int main(){
	int c;
	while(gettoken() != EOF) {
		strcpy(datatype, token);
		out[0] = '\0';
		dcl();
		if(tokentype == ERROR){
			printf("syntax error\n");
		}
		else{
			printf("%s: %s %s\n", name, out, datatype);
		}
		//reset
		bufp = tokentype = 0;
		name[0] = datatype[0] = token[0] = out[0] = '\0';
	}
	return 0;
}


void dcl(void){
	int ns;
	for(ns = 0; gettoken() == '*'; )
		ns++;
	dirdcl();
	if(tokentype != ERROR){
		while(ns-- > 0)
			strcat(out, " pointer to");
	}
}

void dirdcl(void){
	int type;
	if(tokentype == '('){
		dcl();
		if(tokentype != ')'){
			printf("error: missing )\n");
			tokentype = ERROR;
		}
	} else if (tokentype == NAME)
		strcpy(name, token);
	else{
		printf("error: expected name or (dcl)\n");
		tokentype = ERROR;
	}
	if(tokentype != ERROR){

		while((type = gettoken()) == PARENS || type == BRACKETS){
			if(type == PARENS)
				strcat(out, " function returning");
			else {
				strcat(out, " array");
				strcat(out, token);
				strcat(out, " of");
			}
		}
	}
}

int gettoken(void){
	int c, getch(void);
	void ungetch(int);
	char *p = token;
	while((c = getch()) == ' ' || c == '\t')
		;
	if(c == '('){
		while((c = getch()) == ' ')
			;
		if(c  == ')'){ 
			strcpy(token, "()");
			return tokentype = PARENS;
		} else {
			ungetch(c);
			return tokentype = '(';
		}
	} else if (c == '[') {
		for(*p++ = c; (*p++ = getch()) != ']';)
			;
		*p = '\0';
		return tokentype = BRACKETS;
	} else if (isalpha(c)) {
		for(*p++ = c; isalnum(c = getch());)
			*p++ = c;
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	} else
		return tokentype = c;
}

int getch(void){
	return bufp > 0 ? buf[--bufp] : getchar();
}

void ungetch(int c){
	if(bufp >= BUFSIZE)
		printf("ungetch(): too many characters\n");
	else
		buf[bufp++] = c;
}
