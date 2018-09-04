//compile: gcc ex_6-5.c
//run: ./a.out

//Exercise 6-5: Write a function undef that will remove a name and definition from the table maintained by lookup and install.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

struct nlist {
	struct nlist *next;
	char *name;
	char *defn;
};

static struct nlist *hashtab[HASHSIZE];

unsigned hash(char *);
struct nlist *lookup(char *);
char *strd_up(char *);
struct nlist *install(char *, char *);
int undef(char *);

int main(){
	struct nlist *IN = install("IN", "1");
	struct nlist *OUT = install("OUT", "0");
	int worked = undef("IN");
	if(worked && lookup("IN") == NULL)
		printf("just as planned\n");
}

int undef(char *s){
	struct nlist *np;
	int is_first = 0;
	unsigned hashvalue;
	if((np = lookup(s)) == NULL)
		return 0;
	else {
		//if it is first, then freeing must be handled differently
		hashvalue = hash(s);
		np = hashtab[hashvalue]; //pointer to first in list
		if(strcmp(np->name, s) == 0){
		
			hashtab[hashvalue] = np->next; //could be NULL
			free((void *)np->name);
			free((void *)np->defn);
			free(np);
		}
		else{
		
			for(np = hashtab[hashvalue]; np->next != NULL; np = np->next){
				if(strcmp(np->next->name, s) == 0){ 
					break; //found it
				}
			}
			free((void*)np->next->name);
			free((void*)np->next->defn);
			struct nlist *temp = np->next->next;
			free(np->next);
			np->next = temp; //bridge gap
	
		}
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

char *strd_up(char *s){
	char *p = (char *) malloc(strlen(s) - 1);
	if(p != NULL)
		strcpy(p, s);
	return p;
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

