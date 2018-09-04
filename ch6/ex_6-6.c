//compile: gcc ex_6-6.c
//run: ./a.out

//Exercise 6-6: Implement a simple version of the #define processor (i.e., no arguments) suitable for use with C programs, based on the routines of this section. You may also find getch and ungetch helpful.

/*
	Usage: Enter a c program line by line.
	Press EOF when finished
	Program will output new program with defined terms replaced with their definition.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100
#define MAXPROGRAM 10000
#define BUFSIZE 100
#define HASHSIZE 101

#define _ES		0b100000
#define _PP		0b010000
#define _SQ 	0b001000
#define _DQ 	0b000100
#define _SLC	0b000010
#define _MLC	0b000001

#define SQ		'\''
#define DQ		'\"'
#define FS		'/'
#define PP 		'#'
#define ES		'\\'

static struct nlist *hashtab[HASHSIZE];
char *keywords[] = { //we don't want these words to be able to be defined
	"auto",
	"break",
	"case",
	"char",
	"const",
	"continue",
	"default",
	"do",
	"double",
	"else",
	"enum",
	"extern",
	"float",
	"for",
	"goto",
	"if",
	"int",
	"long",
	"register",
	"return",
	"short",
	"signed",
	"sizeof",
	"static",
	"struct",
	"tyepdef",
	"union",
	"unsigned",
	"void",
	"volatile",
	"while"
}; 

#define KEYWORDS (sizeof keywords / sizeof keywords[0])

struct nlist {
	struct nlist *next;
	char *name;
	char *defn;
};

int bufp = 0;
char buf[BUFSIZE];
short state = 0;

unsigned hash(char *);
struct nlist *lookup(char *);
struct nlist *install(char *, char *);
char *strd_up(char *s);
int getch(void);
void ungetch(int c);
int getword(char *, int);

int main(){

	int rv;
	char word[MAXWORD];
	char program[MAXPROGRAM] = {'\0'};
	struct nlist *np = NULL;
	while((rv = getword(word, MAXWORD)) != EOF){
		if(rv == '\n' || rv == ' '){
			strcat(program, word);
		}
		else if((np = lookup(word)) != NULL) 
			strcat(program, np->defn);
		else
			strcat(program, word);
	}
	
	printf("\n\nFull program: \n%s\n", program);
}


int getword(char *s, int max){
	
	int c, definable = 1, i = 0, k = 0;
	char *w = s;	
	char name[MAXWORD] = {'\0'};
	char defn[MAXWORD] = {'\0'};
	c = getch();
	if(c == ' ' || c == '\n'){
		*w++ = c;
		*w = '\0';
		return c;
	}
	if(c == EOF)
		return c;

	if(state&_PP||state&_SQ||state&_DQ||state&_SLC||state&_MLC){
		if(state&_PP){
			while(c != ' ' && c != '\n' && c != EOF && --max > 0){
				*w++ = c;
				c = getch();
			}
			*w = '\0';
			//check if the term is 'define'
			if(strcmp(s, "define") != 0){
				definable = 0;
				state ^= _PP;
			}

			//continue - spaces are legal after 'define'
			while(isspace(c) && c != '\n' && c != EOF && --max > 0){
				*w++ = c;
				c = getch();
			}
			*w = '\0';
			
			//get name
			while(c != ' ' && c != '\n' && c != EOF && --max > 0 && (isalnum(c) || c == '_')) {
				name[i++] = c;
				*w++ = c;
				c = getch();
			}
			name[i] = '\0';
			*w = '\0';
			
			//make sure it is not a keyword
			for(i = 0; k < KEYWORDS; k++){
				if(strcmp(&name[0], keywords[i]) == 0)
					definable = 0;
			}

			//spaces are legal after name
			while(isspace(c) && c != '\n' && c != EOF && --max > 0){
				*w++ = c;
				c = getch();
			}
			*w = '\0';
	
			//string?	
			if(c == DQ || c == SQ){
				*w++ = c;
				state = (c == DQ) ? state|_DQ : state|_SQ;	
				c = getch();
			}
			//get definition
			i = 0;
			while(c != ' ' && c != '\n' && (isalnum(c) || state&_DQ || state&_SQ || state&_ES || c == '\\') && c != EOF && --max > 0 && (isalnum(c) || c == ')' || c == '(' || c == '[' || c == ']' || c == '*' || c == '/' || c == ']' || c == '[' || c == '-')) {
				if(c == DQ && !state&_ES)
					break;
				if(c == '\\')
					state |= _ES;
				else if(state&_ES)
					state ^= ES;	
				*w++ = c;
				defn[i++] = c;
				c = getch();
			}
			if(state&_DQ)
				state ^= _DQ;
			defn[i] = '\0';
			*w = '\0';
			
			//install name-definition
			if(strlen(name) + strlen (defn) + 1 < MAXWORD && strlen(name) > 0 && strlen(defn) > 0 && definable)
			{
				install(&name[0], &defn[0]);
			}
			
			//get rest of line
			while(c != '\n' && c != EOF){
				*w++ = c;
				c = getch();
			}
			if(c != DQ && c != SQ)
				ungetch(c);
			*w = '\0';
			state ^= _PP; 
		}
		else if(state&_SQ){
			while(state&_SQ && c != EOF){
				if(state&_ES)
					state ^= _ES;	
				else if(c == ES)
					state |= _ES;
				else if(c == SQ)
					state ^= _SQ;
				*w++ = c;
				c = getch();
			}
			ungetch(c);
			*w = '\0';
		}
		else if(state&_DQ){
			while(state&_DQ && c != EOF){
				if(state&_ES)
					state ^= _ES;	
				else if(c == ES)
					state |= _ES;
				else if(c == DQ)
					state ^= _DQ;
				*w++ = c;
				c = getch();
			}
			ungetch(c);	
			*w = '\0';
		}
		else if(state&_SLC){
			while(c != '\n' && c != EOF){
				*w++ = c;
				c = getch();
			}
			*w = '\0';
			ungetch(c);
			state ^= _SLC;
		}
		else if(state&_MLC){
			while(state & _MLC && c != EOF){
				*w++ = c;
				if(c == '*'){
					if((c = getch()) == '/'){
						*w++ = c;
						state ^= _MLC;
					}
					else{
						ungetch(c);
					}
				}
				else{
					*w++ = c;
					c = getch();
				}
			}
			*w = '\0';
		}
	}
	//check if we need to be put in a state
	else if(c == SQ || c == DQ || c == FS || c == PP){
		if(c == SQ){ 
			*w++ = c;
			*w = '\0';
			state |= SQ;
		}
		else if(c == DQ){ 
			*w++ = c;
			*w = '\0';
			state |= DQ;
		}
		else if(c == FS){
			*w++ = c;
			if((c = getch()) == '*'){
				*w++ = c;
				*w = '\0';
				state |= _MLC;
			}
			else{
				*w = '\0';
				ungetch(c);
			}
		}
		else if(c == PP){
			*w++ = c;
			*w = '\0';
			state |= _PP;
		}
	}
	else if(!isalnum(c) && c != '_' && c != SQ && c != DQ){
		*w++ = c;
		*w = '\0';
	}
	else {
		printf("String before: %s\n", s);
		*w++ = c;
		//grab word
		for(;--max > 0;){
			c = getch();
			if(c == ' ' || c == '\n' || c == EOF || (!isalnum(c) && c != '_')){
				break;
			}
			*w++ = c;
			
		}
		ungetch(c);
		*w = '\0';
		printf("String: '%s'\n", s);

	}
	return 1;
}


unsigned hash(char *s){
	unsigned hashval;
	for(hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 *hashval;
	return hashval % HASHSIZE;
}

struct nlist *lookup(char *s)
{
	struct nlist *np;
	for(np = hashtab[hash(s)]; np != NULL; np = np->next)
		if(strcmp(s, np->name) == 0)
			return np;
	return NULL;
	
}
struct nlist *install(char *name, char *defn){
	struct nlist *np;
	unsigned hashval;
	if((np = lookup(name)) == NULL){
		np = (struct nlist*) malloc(sizeof(*np));
		if(np == NULL || (np->name = strd_up(name)) == NULL)
			return NULL;
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	} else
		free((void *) np->defn);
	if((np->defn = strd_up(defn)) == NULL)
		return NULL;
	return np;
}

char *strd_up(char *s){
	char *p = (char *) malloc(strlen(s) - 1);
	if(p != NULL)
		strcpy(p, s);
	return p;
}
//getword, no comments or strings
//getch, ungetch
int getch(void){
	return bufp > 0 ? buf[--bufp] : getchar();
}

void ungetch(int c){
	if(bufp >= BUFSIZE)
		printf("ungetch(): too many characters\n");
	else
		buf[bufp++] = c;
}
