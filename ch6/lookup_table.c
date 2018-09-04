//program from section 6.6; replacement text program using hash function

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

int main(){
	struct nlist *IN = install("IN", "1");
	struct nlist *OUT = install("OUT", "0");
	OUT = lookup("IN");
	IN = lookup("OUT");
	printf("%s: %s\n", OUT->name, OUT->defn);
	printf("%s: %s\n", IN->name, IN->defn);

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

