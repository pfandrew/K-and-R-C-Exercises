//compile: gcc ex_7-2.c
//run: ./a.out

//Exercise 7-2: Write a program that will print arbitrary input in a sensible way. As a minimum, it should print non-graphic characters in octal or hexadecimal according to local custom, and break long text lines.

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXWORD 20
#define MAXLINE 30

int main(){
	//collect input
	//print numbers in Hex
	//print at most 30 characters per line

	int c, i = 0, k, position = 0;
	double d;
	char number[MAXWORD];
	while((c = getchar()) != EOF){
		if(c == '\n' || position > MAXLINE - 1){
			putchar('\n');
			position = 0;
		}
		else if(isdigit(c)){
			i = 0;
			while(isdigit(c) && i < MAXWORD - 1){
				position++;
				number[i++] = c;
				c = getchar();
				if(position > MAXLINE - 1){
					putchar('\n');
					position = 0;
				}
			}
			if(c == '.' && i < MAXWORD - 1){
				number[i++] = '.';
				position++;
				if(position > MAXLINE - 1){
					putchar('\n');
					position = 0;
				}
				c = getchar();
				while(isdigit(c) && i < MAXWORD - 1){
					position++;
					number[i++] = c;
					c = getchar();
					if(position > MAXLINE - 1){
						putchar('\n');
						position = 0;
					}
				}
				number[i] = '\0';
				d = atof(&number[0]);
				printf("%f", d);
				if(c != EOF)
					ungetc(c, stdin);
				else
					break;
			}
			else{
				number[i] = '\0';
				k = atoi(&number[0]);
				printf("%X", k);
				if(c != EOF)
					ungetc(c, stdin);
				else
					break;	
			}
		}
		else{
			printf("%c", c);
			position++;
		}
		
	}
}
