//compile: gcc ex_5-17.c -o ex515
//run: ex517 -[dfrn] -[rn]

//Add a field-handling capability, so sorting may be done on fields within lines, each field sorted according to an independent set of options. (The index for this book was sorted with -df for the index category and -n for the page numbers>))


/*
	This program solves the problem for the example itself, not for any type of line entered
	MAX fields: 2
	Types of fields: strings, numbers
	Fields are input seperately with prompt for the user
	no options -> 1 field
	Strings must be input first
	sorting by strings can only be done between lines (line 1 is sorted relative to the rest of the lines, etc.)
	sorting numbers results in number strings being sorted with numbers in that string
	numbers can be sorted in reverse (-rn)	
	strings can use all operators -rndf
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINES 5000
#define MAXFIELDS 2
#define MAXCATLEN 100
#define MAXLINE MAXFIELDS*MAXCATLEN
#define ALLOCSIZE MAXLINES*MAXLINE
#define MAXNUMS 15

//buffers/data
char *lineptr[MAXLINES];
static char buf[ALLOCSIZE];
static int buf_i;

//program options
#define NUMERIC 	0b0001
#define REVERSE 	0b0010
#define FOLD		0b0100
#define DIRECTORY 	0b1000

static int flags[MAXFIELDS] = {0,0};

//functions
int readlines(char *lp[], int nlines, int);
int get_line(char s[], int maxline);
void writelines(char *lp[], int);
void q_sort(void *lp[], int left, int right, 
					int (*comp)(void *, void *));

int sortbyfield(char *lp[], int, int);
int numcmp(char *, char *);
int str_cmp(char *s, char *t);
char* find_next(char *);

int main(int argc, char *argv[]){
	
	int nlines, field = 0;
	char flag;

	//process flags for fields
	while(--argc > 0 && **++argv == '-'){
		while((flag = *++*argv)){
			switch(flag){
				case 'n': flags[field] = (flags[field]|NUMERIC); break;
				case 'r': flags[field] = (flags[field]|REVERSE); break;
				case 'f': flags[field] = (flags[field]|FOLD); break;
				case 'd': flags[field] = (flags[field]|DIRECTORY); break;
				default : printf("usage: ex517 -[r, n, f, d]"); return 0;
			}
		}
		field++;
	}

	if(field == 0)
		field++;
	
	//read in field lines, allocate them to buffer, seperate them by newline for processing

	if((nlines = readlines(lineptr, MAXLINES, field)) >= 0){
		sortbyfield(lineptr, nlines, field);
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("something has gone horribly wrong...\n");
		return 1;
	}

}

int sortbyfield(char *v[], int lines, int field){
	//sort numbers first
	char* numstring[MAXNUMS];
	char numbuf[MAXCATLEN];
	int numbuf_i = 0, numstart = 0, k = 0, numstringdone = 0, nums = 0;
	char** v_origin = v;
	char *origin;
	char *t;

	//sort numbers first
	if(field > 1){
		//break string into multiple strings for sorting
		for(int i = 0; i < lines; i++, v++){
			t = *v;
			numstringdone = numbuf_i = nums = k = numstart = 0;
			while(*t != '\n')
				t++;
			while(*t == '\n') //original lines have field breaks w/ newline
			{
				*t = ' ';
				t++;
			}
			origin = t;
			while(isspace(*t))
			{
				(*t)++;
			}
			while(!numstringdone){
				if(*t == ' ' || *t == '\n'){
					nums++;
					numbuf[numbuf_i++] = ' ';
					numbuf[numbuf_i++] = '\0';
					numstring[k++] = &numbuf[numstart];
					numstart = numbuf_i;
				}
				else{
					numbuf[numbuf_i++] = *t;
				}

				if(*t == '\0'){
					numstringdone = 1;
				}
				else
					*t++;
				
			}
			
			//sort numbers
			q_sort((void **)numstring, 0, k - 1, (int(*)(void *, void *))numcmp);
			
			//copy sorted numbers back into original memory, perhaps in reverse
			int j = (flags[1]&REVERSE) ? nums - 1 : 0;
			int inc = (flags[1]&REVERSE) ? -1 : 1;
			for(; j < nums && j >= 0; j += inc){
				strcpy(origin, numstring[j]);
				origin += strlen(numstring[j]);
			}
			*--origin = '\n';
		}	
	}

	//now sort by first field
	q_sort((void**)v_origin, 0, lines - 1, (int(*)(void *, void *))str_cmp);	
}

int readlines(char *lineptr[], int nlines, int field){
	int len, i, k, linestart, entering = 1;
	char line[MAXLINE];

	while(i < MAXLINES && entering){
		linestart = buf_i;
		for(k = 0; k < field; k++){
			printf("Data for line %d, field %d:\n\t", i + 1, k + 1);
			if((len = get_line(line, MAXCATLEN)) > 0 && len + buf_i < ALLOCSIZE){
				strcpy(&buf[buf_i], line);
				buf_i += len;
			}
			else{
				if(len)
					printf("error: not enough storage\n");
				else
					printf("////////ENTRY_ENDED////////\n");
				k = field;
				entering = 0;
			} 	
		}	
		if(entering){
			buf[buf_i++] = '\0';
			lineptr[i++] = &buf[linestart];
		}
	}

	return i;
}
int get_line(char s[], int maxline){
	int i = 0, c;
	while((c = getchar()) != EOF && c != '\n')
		s[i++] = c;

	if(c == '\n')
		s[i++] = '\n';
	s[i] = '\0';
	return i;
}
void writelines(char *lineptr[], int nlines){
	int i = flags[0]&REVERSE?nlines - 1 : 0;
	int inc = flags[0]&REVERSE?-1:1;
	for(; i >=0 && i < nlines; i += inc){
		printf("%s", lineptr[i]);
	}
}

void q_sort(void *lineptr[], int left, int right, int(*comp)(void *, void *)){
	int i, last;
	void swap(void *v[], int, int);
	if(left >= right)
		return;
	swap(lineptr, left, (left+right)/2);
	last = left;
	for(i = left + 1; i <= right; i++){
		if((*comp)(lineptr[i], lineptr[left]) < 0){
			swap(lineptr, ++last, i);
		}
	}
	swap(lineptr, left, last);
	q_sort(lineptr, left, last - 1, comp);
	q_sort(lineptr, last + 1, right, comp);
}

void swap(void *v[], int left, int right){
	void* tmp = v[left]; 
	v[left] = v[right]; 
	v[right] = tmp;
}

int numcmp(char *s1, char *s2){
	double v1, v2;
	v1 = atof(s1);
	v2 = atof(s2);
	if(v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

int str_cmp(char *s, char *t){
	if(DIRECTORY & flags[0]){
		while(!isalnum(*s) && !isspace(*s) && *s != '\0'){
			s++;
		}
		while(!isalnum(*t) && !isspace(*t) && *t != '\0'){
			t++;
		}
		
	}
	
	while(*s == *t || (FOLD&flags[0])*(tolower(*s) == tolower(*t))){
		if(*s == '\0') 
			return 0;
		
		s++;
		t++;
		
		if(DIRECTORY&flags[0]){
			while(!isalnum(*s) && !isspace(*s) && *s != '\0'){
				s++;
			}
			while(!isalnum(*t) && !isspace(*t) && *t != '\0'){
				t++;
			}
		}
		
	}
	return *s - *t;
}

char *find_next(char *s){
	while(!isalnum(*s) && !isspace(*s) && *s != '\0')
		s++;
	return s;
}

