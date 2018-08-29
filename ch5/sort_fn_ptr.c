//program from section 5.11; uses qsort in combination with function pointers

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 5000
#define MAXLINE 100
#define ALLOCSIZE MAXLINES*MAXLINE

char *lineptr[MAXLINES];
static char buf[ALLOCSIZE];
static int buf_i;

int readlines(char *lineptr[], int nlines);
int get_line(char s[], int maxline);
void writelines(char *lineptr[], int nlines);
void q_sort(void *llineptr[], int left, int right, 
					int (*comp)(void *, void *));

int numcmp(char *, char *);

int main(int argc, char *argv[]){
	
	int nlines;
	int numeric = 0;

	if(argc > 1 && strcmp(argv[1], "-n") == 0)
		numeric = 1;
	if((nlines = readlines(lineptr, MAXLINES)) >= 0){
		q_sort((void **) lineptr, 0, nlines - 1,
			(int (*)(void *, void *)) (numeric ? numcmp : strcmp));
		writelines(lineptr, nlines);
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
void writelines(char *lineptr[], int nlines){
	int i;
	for(i = 0; i < nlines; i++){
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
