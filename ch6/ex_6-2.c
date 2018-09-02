//compile: gcc ex_6-2.c -o cmplen
//run: cmplen -n

//Exercise 6-2: Write a program that reads a C program and prints in alphabetical order each group of variable names that are identical in the first 6 characters, but different somwhere thereafter. Don't count words within strings and comments. Make 6 a parameter that can be set from the command line.

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXWORD 100
#define MAXCMP  6
#define BUFSIZE 100

#define _ES	0b100000
#define _PP	0b010000
#define _SQ 	0b001000
#define _DQ 	0b000100
#define _SLC	0b000010
#define _MLC	0b000001

#define SQ		'\''
#define DQ		'\"'
#define FS		'/'
#define PP 		'#'
#define ES		'\\'

struct node {
	char *variable;
	int count;
	struct node *left;
	struct node *right;
}; 

static int complen;
int state = 0;
int bufp;
char buf[BUFSIZE];

char *keywords[] = { //we don't want these words
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

int getword(char *, int);
int str_cmp(char *, char *, int);
char *strd_up(char *);
struct node *talloc(void);
struct node *addtree(struct node *, char *);
void treefree(struct node *);
void treeprint(struct node *);
int getch(void);
void ungetch(int);


int main(int argc, char *argv[])
{	
	//check if comparison length is set from command line
	if(argc > 1 && **++argv != '-'){
		printf("usage: cmplen -n\n");
		return 0;
	}
	else if(argc > 1)
		complen = atof(++*argv);
	else
		complen = MAXCMP;

	//start getting words
	int rv = 0;
	char word[MAXWORD];
	struct node *root = NULL;
	while((rv = getword(word, MAXWORD)) != EOF){
		if(rv > 0)
			root = addtree(root, word);
	}
	treeprint(root);
	treefree(root);

	return 0;
}

int str_cmp(char *s, char *t, int maxlen){
	while(*s == *t && --maxlen > 0)
		if(*s == '\0')
			return 0;
		else{
			s++;
			t++;
		}
	return *s - *t;
}

struct node *talloc(void){
	return (struct node*) malloc(sizeof(struct node));
}

char *strd_up(char *s){
	char *p;
	p = (char *) malloc(strlen(s) + 1);
	if(p != NULL)
		strcpy(p, s);
	return p;
}

struct node *addtree(struct node * n, char *s)
{
	int cond;
	if(n == NULL){
		n = talloc();
		n->variable = strd_up(s);
		n->count++;
		n->left = n->right = NULL;
	}
	else if((cond = str_cmp(n->variable, s, complen)) == 0){
		if(strcmp(s, n->variable) == 0)
			n->count++;
		else
			n->left = addtree(n->left, s);
	}
	else if (cond < 0){
		n->right = addtree(n->right, s);
	}
	else
		n->left = addtree(n->left, s);
	return n;
}

void treeprint(struct node * n){
	if(n != NULL){
		treeprint(n->left);
		printf("%4d %s\n", n->count, n->variable);
		treeprint(n->right);
	}
}

void treefree(struct node *n){
	if(n != NULL){
		free(n->variable);
		treefree(n->left);
		treefree(n->right);
		free(n);
	}
}

int getword(char *s, int max){
	int c;
	char *w = s;	
	while(isspace(c = getch()))
		;

	//check if we are in a state
	if(c == EOF)
		return c;
	if(state&_PP||state&_SQ||state&_DQ||state&_SLC||state&_MLC){
		if(state&_PP){
			while(c != ' ' && c != '\n' && c != EOF) 
				c = getch();
			ungetch(c);
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
				c = getch();
			}
			ungetch(c);
		}
		else if(state&_DQ){
			while(state&_DQ && c != EOF){
				if(state&_ES)
					state ^= _ES;	
				else if(c == ES)
					state |= _ES;
				else if(c == DQ)
					state ^= _DQ;
				c = getch();
			}
			ungetch(c);	
		}
		else if(state&_SLC){
			while(c != '\n' && c != EOF)
				c = getch();
			ungetch(c);
			state ^= _SLC;
		}
		else if(state&_MLC){
			while(state & _MLC && c != EOF){
				if(c == '*'){
					if((c = getch()) == '/'){
						state ^= _MLC;
					}
					else
						ungetch(c);
				}
				else
					c = getch();
			}
		}
	}
	//check if we need to be put in a state
	else if(c == SQ || c == DQ || c == FS || c == PP){
		if(c == SQ) state |= SQ;
		else if(c == DQ) state |= DQ;
		else if(c == FS){
			if((c = getch()) == '*')
				state |= _MLC;
			else
				ungetch(c);
		}
		else if(c == PP)
			state |= _PP;
	}
	//variable names cannot start with non-alpha characters, other than underscore
	else if (isalpha(c) || c == '_'){
		*w++ = c;
		//grab word
		for(;--max > 0; w++){
			if(!isalnum(*w = getch()) && *w != '_'){
				ungetch(*w);
				break;
			}
		}
		*w = '\0';

		//compare to keywords
		int is_keyword = 0;
		for(int i = 0; i < KEYWORDS; i++){
			if(strcmp(s, keywords[i]) == 0){
				is_keyword = 1;
				break;
			}
		}
		if(!is_keyword)
			return 1;
	}
	return 0;
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
