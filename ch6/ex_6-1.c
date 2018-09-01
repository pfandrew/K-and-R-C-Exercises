//compile: gcc ex_6-1.c
//run: ./a.out

//Exercise 6-1: Our version of getword does not properly handle underscores, string constants, comments, or preprocessor control lines. Write a better version.

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define BUFSIZE 100
#define _SQ	0b000001
#define _DQ	0b000010
#define _SLC	0b000100
#define _MLC 	0b001000
#define _PP	0b010000
#define _ES	0b100000

#define SQ 	'\''
#define DQ	'\"'
#define FS	'/'
#define ES 	'\\'
#define PP 	'#'
#define US 	'_'

short state = 0;

char buf[BUFSIZE];
int bufp = 0;

struct key {
	char *word;
	int count;
} keytab[] = { //this part sets aside storage
	"auto", 0,
	"break", 0,
	"case", 0,
	"char", 0,
	"const", 0,
	"continue", 0,
	"default", 0,
	"do", 0,
	"double", 0,
	"else", 0,
	"enum", 0 ,
	"extern", 0,
	"float", 0,
	"for", 0,
	"goto", 0,
	"if", 0,
	"int", 0,
	"long", 0,
	"register", 0,
	"return", 0,
	"short", 0,
	"signed", 0,
	"sizeof", 0,
	"static", 0,
	"struct", 0,
	"tyepdef", 0,
	"union", 0,
	"unsigned", 0,
	"void", 0,
	"volatile", 0,
	"while", 0
}; 

#define NKEYS (sizeof keytab/sizeof(struct key))

int getch(void);
void ungetch(int);
int getword(char *, int);
int binsearch(char *, struct key *, int);

int main(){
	int n;
	char word[MAXWORD];
	
	while(getword(word, MAXWORD) != EOF){
		if(isalpha(word[0])){
			if((n = binsearch(word, keytab, NKEYS)) >= 0)
				keytab[n].count++;
		}
	}
	for(n = 0; n < NKEYS; n++){
		if(keytab[n].count > 0)
			printf("%4d %s\n", keytab[n].count, keytab[n].word);
	}
	return 0;
}

int getword(char *word, int lim){
	int c, last, getch(void);
	void ungetch(int);
		
	char *w = word;

	while(isspace(c = getch()))
		;
	
	if(c != EOF)
		*w++ = c;
	
	//check if we are in a state which would invalidate usage of word
	if(state&_SQ || state&_DQ || state&_MLC || state&_SLC || state&_PP){
		if(state&_SLC){
			while(c != '\n'){
				c = getch();
			}
			state = state^_SLC;
		}
		else if(state&_MLC){
			while(state&_MLC && c != EOF){
				if(c == '*') 
				{
					if((c = getch()) == '/')
						state = state^_MLC;
				}
				else
					c = getch();
			}
			if(c == EOF)
				ungetch(c);
		}
		else if(state&_DQ){
			while(state&_DQ && c != EOF){
				if(state&_ES){
					state = state^_ES;
				}
				else if(c == '\\'){
					state = state|_ES;
				}
				else if(c == '\"'){
					state = state^_DQ;
				}

				c = getch();
			}
			if(c == EOF)
				ungetch(c);
		}
		else if(state&_SQ){
			while(state&_SQ){
				if(state&_ES){
					state = state^_ES;
				}
				else if(c == '\\'){
					state = state|_ES;
				}
				else if(c == '\''){
					state = state^_DQ;
				}

				c = getch();
			}
		}
		else if(state&_PP){
			while(c != '\n')
				c = getch();
			state = state^_PP;
		}
	}

	//check if we need to put the program into a state	
	else if(c == US || c == FS || c == SQ || c == DQ || c == ES || c == PP){
		switch(c){
			case US: /*supposes that underscore invalidates usage as a keyword*/
				while(c != ' ' && c!= '\n' && c != EOF) 
					c = getch();
				ungetch(c);
				break;
			case FS:
				last = c;
				if((c = getch()) == FS)
					state = state|_SLC;
				else if(c == '*')
					state = state|_MLC;
				else
					ungetch(c);
				break;
			case ES: //supposes that ES invalidates usage as a keyword
				while(c != ' ' && c != '\n' && c != EOF)
					c = getch();
				ungetch(c);
				break;
			case DQ:
				state = state|_DQ;
				break;
			case SQ:
				state = state|_SQ;
				break;
			case PP:
				state = state|_PP;
				break;
			default:
				printf("Something has gone horribly wrong in this if/else nightmare\n");
				break;
		}
	}
	//no need for these
	else if(!isalpha(c)){
		*w = '\0';
		return c;
	}
	//finally, process the word
	else{
		for(; --lim > 0; w++){
			if(!isalnum(*w = getch())){
				ungetch(*w);
				break;
			}
		}
		*w = '\0';
		return word[0];
	}
}

int binsearch(char *word, struct key tab[], int n){
	int cond, low, high, mid;
	low = 0;
	high = n - 1;
	while(low <= high){
		mid = (low+high)/2;
		if((cond = strcmp(word, tab[mid].word)) < 0)
			high = mid - 1;
		else if(cond > 0)
			low = mid + 1;
		else
			return mid;
	}
	return -1;
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
