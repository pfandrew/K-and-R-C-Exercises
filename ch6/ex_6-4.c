//compile: gcc ex_6-4.c
//run: ./a.out

//Exercise 6-4: Write a program that prints the distinct words in its input sorted into decreasing order of frequency of occurrence. Precede each word by its count.


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXWORD 100
#define BUFSIZE 100

struct node {
	char *word;
	int count;
	struct node *next;
	struct node *left;
	struct node *right;
}; 

int bufp;
char buf[BUFSIZE];

int getword(char *, int);
int getch(void);
void ungetch(int);

char *strd_up(char *);
struct node *talloc(void);

struct node *addlink(struct node *, char *);
struct node *addtree(struct node *, struct node *);

void chainfree(struct node *);
void treefree(struct node *);
void treeprint(struct node *);

int numcmp(int, int);

int main(int argc, char *argv[])
{	
	int rv = 0;
	char word[MAXWORD];
	struct node *root = NULL;
	while((rv = getword(word, MAXWORD)) != EOF){
		if(rv > 0){
			root = addlink(root, word);
		}
			
	}
	struct node *root2 = NULL;
	struct node *p = root;
	
	//make new tree from existing chain
	while(p != NULL){
		root2 = addtree(root2, p);
		p = p->next;
	}
	treeprint(root2);
	chainfree(root);
	treefree(root2);
	return 0;
}

int numcmp(int a, int b){
	return a - b;
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

struct node *addtree(struct node *n, struct node *old){
	int cond;
	if(n == NULL){
		n = talloc();
		n->word = old->word; //it is a pointer to previously allocated memory
		n->count = old->count; //memory for int allocated just now
		n->left = n->right = NULL;
	}
	else if((cond = numcmp(old->count, n->count)) < 0){
		n->left = addtree(n->left, old);
	}
	else
		n->right = addtree(n->right, old);
	return n;
		
}

struct node * addlink(struct node * n, char *s)
{
	if(n == NULL){
		n = talloc();
		n->word = strd_up(s);
		n->count = 1;
		n->next = NULL;
	}
	else if(strcmp(n->word, s) == 0)
		n->count++;
	else
		n->next = addlink(n->next, s);
	return n;
}

void treeprint(struct node * n){
	if(n != NULL){
		treeprint(n->right);
		printf("%4d: %s\n", n->count, n->word);
		treeprint(n->left);
	}
}

void chainfree(struct node *n){
	if(n != NULL){
		free(n->word);
		chainfree(n->next);
		free(n);
	}
}

//string memory has already been freed by chain free
void treefree(struct node *n){
	if(n != NULL){
		treefree(n->left);
		treefree(n->right);
		free(n);
	}
}

int getword(char *s, int max){
	int c;
	char *w = s;	
	c = getch();
	if(c == EOF)
		return c;
	else if(c == '\n')
		return 0;	
	while(isspace(c))
		c = getch();
	if (isalpha(c)){
		*w++ = c;
		//grab word
		for(;--max > 0; w++){
			if(!isalnum(*w = getch())){
				ungetch(*w);
				break;
			}
		}
		*w = '\0';

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
