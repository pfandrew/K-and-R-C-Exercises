//compile: gcc ex_5-20.c
//run: ./a.out

//Exercise 5-20: Expand dcl to handle declarations with function argument types, qualifiers like const, and so on.

/*
	IN:
	const int comp(int, int, int)

	OUT:
	comp:  function with argument(s) (int, int, int) returning const int 	

	NO ERROR type
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define BUFSIZE 100
#define NUMTYPES 6

enum { NAME, PARENS, BRACKETS, ARGUMENTS };

void dcl(void);
void dirdcl(void);
int gettoken(void);
int getch(void);
void ungetch(int);


int tokentype;
char token[MAXTOKEN] = {'\0'};
char name[MAXTOKEN];
char datatype[MAXTOKEN] = {'\0'};
char out[1000];
char buf[BUFSIZE];
int bufp = 0;
char *data_types[] = {"const", "int", "char", "void", "double", "float"};

int main(){
	while(gettoken() != EOF) {
		strcpy(datatype, token);
		out[0] = '\0';
		dcl();
		if(tokentype != '\n')
			printf("syntax error\n");
		printf("%s: %s %s\n", name, out, datatype);
		datatype[0] = token[0] = out[0] = '\0';
	}
	return 0;
}


void dcl(void){
	int ns;
	for(ns = 0; gettoken() == '*'; )
		ns++;
	dirdcl();
	while(ns-- > 0)
		strcat(out, " pointer to");
}

void dirdcl(void){
	int type;
	if(tokentype == '('){
		dcl();
		if(tokentype != ')')
			printf("error: missing )\n");
	} else if (tokentype == NAME)
		strcpy(name, token);
	else
		printf("error: expected name or (dcl)\n");
	while((type = gettoken()) == PARENS || type == BRACKETS || type == ARGUMENTS){
		if(type == PARENS)
			strcat(out, " function returning");
		else if(type == ARGUMENTS){
			strcat(out, " function with argument(s) (");
			strcat(out, token);
			strcat(out, ") returning");
		}
		else {
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
	}
}


int gettoken(void){
	int c, getch(void);
	void ungetch(int);
	char *p = token;
	char dt[MAXTOKEN];
	int valid_dt, parsing = 1;
	valid_dt = 0;	

	while((c = getch()) == ' ' || c == '\t')
		;
	if(c == '('){
		if((c = getch()) == ')'){
			strcpy(token, "()");
			return tokentype = PARENS;
		} 
		else{
			ungetch(c);
		}
		while((c = getch()) == ' ' || isalnum(c) || c == ',' || c == '*' || c == '[' || c == ']')
			*p++ = c;
		if(c == ')')
			return tokentype = ARGUMENTS;	
		else {
			ungetch(c);
			return tokentype = '(';
		}
	} else if (c == '[') {
		for(*p++ = c; (*p++ = getch()) != ']';)
			;
		*p = '\0';
		return tokentype = BRACKETS;
	}
	else if (isalpha(c)){
		//check if we have already gotten the data type
		if(strlen(datatype) == 0){
			while(parsing){	
				while(c == ' ')
					c = getch();
				int i = 0;
				for(dt[i++] = c; isalnum(c = getch()); i++)
					dt[i] = c;
				dt[i] = '\0';
				for(i = 0; i < NUMTYPES; i++){
					if(strcmp(dt, data_types[i]) == 0) 
						valid_dt = 1;
				}
				if(valid_dt){
					strcat(token, dt);
					strcat(token, " ");
					valid_dt = 0;
				}
				else{
					ungetch(c);
					for(i = strlen(dt) - 1; i >= 0; i--){
						ungetch(dt[i]); //push it all back onto input, as it is a name;
					}
					parsing = 0;
				}
			}
			
		} 
		else{
			for(*p++ = c; isalnum(c = getch());)
				*p++ = c;
			*p = '\0';
			ungetch(c);
		}
		return tokentype = NAME;	
	} 
	else
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
