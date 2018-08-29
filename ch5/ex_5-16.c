//compile: gcc ex_5-16.c -o ex516
//run: ex516 -[r, n, f, d]

//Exercise 5-16: Add the -d ("directory order") option, which makes comparisons only on letters, numbers and blanks. Make sure it works in conjunction with f.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINES 5000
#define MAXLINE 100
#define ALLOCSIZE MAXLINES*MAXLINE

//buffers/data
char *lineptr[MAXLINES];
static char buf[ALLOCSIZE];
static int buf_i;

//program options
static int numeric = 0;
static int reverse = 0;
static int fold = 0;
static int dir = 0;

//functions
int readlines(char *lineptr[], int nlines);
int get_line(char s[], int maxline);
void writelines(char *lineptr[], int nlines, int reverse);
void q_sort(void *llineptr[], int left, int right, 
					int (*comp)(void *, void *));

int numcmp(char *, char *);
int str_cmp(char *s, char *t);
char* find_next(char *);

int main(int argc, char *argv[]){
	
	int nlines;
	char flag;

	while(--argc > 0 && **++argv == '-'){
		while((flag = *++*argv)){
			switch(flag){
				case 'n': numeric = 1; break;
				case 'r': reverse = 1; break;
				case 'f': fold = 1; break;
				case 'd': dir = 1; break;
				default : printf("usage: ex516 -[r, n, f, d]"); break;
			}
		}
	}

	if((nlines = readlines(lineptr, MAXLINES)) >= 0){
		q_sort((void **) lineptr, 0, nlines - 1,
			(int (*)(void *, void *)) (numeric ? numcmp : str_cmp));
		writelines(lineptr, nlines, reverse);
		return 0;
	} else {
		printf("Input too big to sort\n");
		return 1;
	}

}

int readlines(char *lineptr[], int nlines){
	int len, i = 0;
	char line[MAXLINE];
	while(i < MAXLINES && (len = get_line(line, MAXLINE)) > 0){
		if(buf_i + len < ALLOCSIZE){
			lineptr[i++] = strcpy(&buf[buf_i], line);
			buf_i += len + 1;
		}
		else
			printf("No more space for line '%s'\n", line);
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
void writelines(char *lineptr[], int nlines, int reverse){
	int i = reverse ? nlines - 1 : 0;
	int inc = reverse ? -1 : 1;
	for(; i >= 0 && i < nlines; i += inc){
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
	if(dir){
		while(!isalnum(*s) && !isspace(*s) && *s != '\0'){
			s++;
		}
		while(!isalnum(*t) && !isspace(*t) && *t != '\0'){
			t++;
		}
		
	}
	
	while(*s == *t || fold*(tolower(*s) == tolower(*t))){
		if(*s == '\0') 
			return 0;
		
		s++;
		t++;
		
		if(dir){
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
