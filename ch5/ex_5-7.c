//compile: gcc ex_5-7.c
//run: ./a.out

//Exercise 5-7: Rewrite readlines to store lines in an array supplied by main, rather than calling alloc to maintain storage. How much faster in the program?

#include <stdio.h>
#include <string.h>

#define MAXLINES 5000
#define MAXLEN 1000
#define ALLOCSIZE 10000

int get_line(char *, int);
int readlines(char *lineptr[], char buf[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);

int main(){
	int nlines;
	char *lineptr[MAXLINES];
	char allocbuf[ALLOCSIZE];
	if((nlines = readlines(lineptr, allocbuf, MAXLINES)) >= 0){
		qsort(lineptr, 0, nlines - 1);
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("error: input too big to sort\n");
		return 1;
	}
}

int readlines(char *lineptr[], char buf[], int maxlines){
	int len, nlines, counter = 0;
	char *p, line[MAXLEN];
	nlines = 0;
	while ((len = get_line(line, MAXLEN)) > 0){
		if(nlines >= maxlines && counter + len >= ALLOCSIZE){
			return -1;
		}
		else{
			line[len - 1] = '\0';
			strcpy(buf, line); //copy line characters into buf
			lineptr[nlines++] = buf;//assign address of string in buf to lineptr for writing 
			buf += len; //move buf up to next spot
			counter += len;
		}
	}
	return nlines;
}

void writelines(char *lineptr[], int nlines){
	int i;
	for(i = 0; i < nlines; i++)
		printf("%s\n", lineptr[i]);
}

void qsort(char *v[], int left, int right){
	int i, last;
	if(left >= right)
		return;
	void swap(char *v[], int i, int j);
	swap(v, left, (left + right)/2);
	last = left;
	for(i = left + 1; i <= right; i++){
		if(strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);
	}
	swap(v, left, last);
	qsort(v, left, last - 1);
	qsort(v, last + 1, right);
}

void swap(char *v[], int i, int j){
	char* tmp = v[i];
	v[i] = v[j];
	v[j] = tmp;
}

int get_line(char s[], int lim){
	int i = 0, c;
	while(i < MAXLEN - 1 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;
	if(c == '\n')
		s[i++] = '\n';
	s[i] = '\0';
	return i;
}
