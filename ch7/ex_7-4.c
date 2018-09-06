//compile: gcc ex_7-4.c
//eun: ./a.out

//Exercise 7-4: Write a private version of scanf analogous to minprintf from the previous section.

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAXINT 10
#define MAXS 50
#define MAXLINE 1000
void minscanf(char *, ...);

int main(){
	char name[MAXS];
	int a, h;
	minscanf("Name: %s, Age: %d, Height (inches): %d\n", name, &a, &h);
}


//ignore blanks and tabs
//
void minscanf(char *fmt, ...){
	va_list ap;
	va_start(ap, fmt);
	int *ival, c, i;
	char cval[2];
	char n[MAXINT];
	char *sval;
	char *p;
	char *q;
	char out[MAXLINE] = {'\0'};

	//detect argument
	//read input
	//store input in variable
	//print input
	va_start(ap, fmt);
	for(p = fmt; *p; p++){
		if(*p != '%'){
			cval[0] = *p;
			cval[1] = '\0';
			strcat(out, cval);
			continue;
		}

		while(isspace(c = getchar()))
			;	

		switch(*++p){
			case 'd': 
				q = n;
				ival = va_arg(ap, int*); //point to first pointer in list
				while(isdigit(c)){
					*q++ = c;
					c = getchar();
				}
				ungetc(c, stdin);
				*q = '\0';
				strcat(out, n);
			break;
			case 'c':
				sval = va_arg(ap, char*);
				*sval++ = c;
				*sval = '\0';
				strcat(out, sval);
				break;
			case 's':
				i = 0; 
				sval = va_arg(ap, char*);
				while(i < MAXS - 1 && !isspace(c)){
					*sval++ = c;
					c = getchar();
					i++;
				}
				*sval = '\0';
				strcat(out, (sval - i));
				break;
			default: printf("unrecognized conversion specifier '%c'\n", *p);
		}
	}
	printf("%s", out);
	va_end(ap);
}
