//compile: gcc ex_5-19.c
//run: ./a.out

//Exercise 5-19: Modify undcl so that it does not add redundant parentheses to declarations.

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define BUFSIZE 100

enum { NAME, PARENS, BRACKETS };

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

int main(){
	int type;
	char temp[MAXTOKEN];

	while(gettoken() != EOF){
		strcpy(out, token);
		while((type = gettoken()) != '\n'){
			if(type == PARENS || type == BRACKETS)
				if(out[0] == '*'){
					sprintf(temp, "(%s)%s", out, token);
					strcpy(out, temp);
				}
				else
					strcat(out, token);
			else if (type == '*') {
				sprintf(temp, "*%s", out);
				strcpy(out, temp);
			} else if (type == NAME) {
				sprintf(temp, "%s %s", token, out);
				strcpy(out, temp);
			} else
				printf("invalid input at %s\n", token);
		}
		printf("%s\n", out);
	}
	return 0;
}

int gettoken(void){
	int c, getch(void);
	void ungetch(int);
	char* p = token;
	while((c = getch()) == ' ' || c == '\t')
		;
	if(c == '('){
		if((c = getch()) == ')'){
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
