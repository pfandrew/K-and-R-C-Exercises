//compile: gcc ex_6-3.c
//run: ./a.out

//Exercise 6-3: Write a cross-referencer that prints a list of all words in a document, and, for each word, a list of the line numbers on which it occurs. Remove noise words like "the", "and" and so on.
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXWORD 100
#define BUFSIZE 100

char* noise[] = {
	"the",
	"and",
	"of",
	"a",
	"an",
	"as",
	"at",
	"in",
	"it",
	"is"
};

#define NOISEWORDS (sizeof noise / sizeof noise[0])

struct lnode {
	int line_no;
	struct lnode *next;
};

struct node {
	char *word;
	struct lnode *line;
	struct node *left;
	struct node *right;
}; 

int bufp;
char buf[BUFSIZE];
int curr_line = 1;

int getword(char *, int);
char *strd_up(char *);
struct node *talloc(void);
struct lnode *lalloc(void);
struct node *addtree(struct node *, char *);
void treefree(struct node *);
void free_list(struct lnode *);
void treeprint(struct node *);
int getch(void);
void ungetch(int);

int main(int argc, char *argv[])
{	
	int rv = 0;
	char word[MAXWORD];
	struct node *root = NULL;
	while((rv = getword(word, MAXWORD)) != EOF){
		if(rv == '\n')
			curr_line++;
		else if(rv > 0){
			root = addtree(root, word);
		}
			
	}
	treeprint(root);
	treefree(root);

	return 0;
}
struct node *talloc(void){
	return (struct node*) malloc(sizeof(struct node));
}

struct lnode *lalloc(void){
	return (struct lnode*) malloc(sizeof(struct lnode));
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
		n->word = strd_up(s);
		n->left = n->right = NULL;
	
		//variable length list of lines need memory	
		n->line = lalloc();
		n->line->line_no = curr_line;
		n->line->next = NULL;

	}
	else if((cond = strcmp(n->word, s)) == 0){
		struct lnode *p = n->line;
		while(p->next != NULL)
			p = p->next;
		if(p->line_no != curr_line){
			p->next = lalloc();
			p->next->line_no = curr_line;
			p->next->next = NULL;	
		}
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
		printf("'%s': [", n->word);
		struct lnode *p = n->line;
		while(p != NULL){
			printf("%d,", p->line_no);
			p = p->next;
		}
		printf("\b]\n");
		treeprint(n->right);
	}
}

void treefree(struct node *n){
	if(n != NULL){
		free(n->word);
		free_list(n->line);
		treefree(n->left);
		treefree(n->right);
		free(n);
	}
}

void free_list(struct lnode * p){
	if(p->next != NULL)
		free_list(p->next);
	free(p);
}

int getword(char *s, int max){
	int c;
	char *w = s;	
	c = getch();
	if(c == EOF || c == '\n')
		return c;	
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

		//compare to noise keywords
		int is_noise = 0;
		for(int i = 0; i < NOISEWORDS; i++){
			if(strcmp(s, noise[i]) == 0){
				is_noise = 1;
				break;
			}
		}
		if(!is_noise)
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
