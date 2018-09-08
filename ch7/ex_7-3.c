//compile: gcc ex_7-3.c
//run: ./a.out

//Exercise 7-3: Revise minprintf to handle more of the other facilities of printf.
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 100

void minprintf(char *fmt, ...);


int main(){
	minprintf("I have %hd friends but one lost his %15.10s so technically only %f.", 66000, "hello, world", 2.84);
}

void minprintf(char *fmt, ...){
	va_list ap;
	char *p, *sval;
	int ival;
	short shval;
	long lval;
	double dval;
	char minwidth[MAX];
	char prec[MAX];
	int left_adj, min_width, precision, is_h = 0, is_l = 0, k = 0, padding, len;

	va_start(ap, fmt);
	for(p = fmt; *p; p++){
		if(*p != '%'){
			putchar(*p);
			continue;
		}

		//looking for: 1) -, 2) min_width, 3) period, 4) precision, 5) h

		//left-adjusted?
		if(*++p == '-'){
			left_adj = 1;
			++p;
		}
		else
			left_adj = 0;

		//min-width - string must take up this amount
		while(isdigit(*p))
			minwidth[k++] = *p++;
		minwidth[k] = '\0';
		if(k == 0)
			min_width = -1;
		else
			min_width = atoi(&minwidth[0]);

		if(*p == '.')
			p++;
		
		//precision - only print this amount after the start of the string
		k = 0;
		while(isdigit(*p))
			prec[k++] = *p++;
		if(k == 0)
			precision = -1;
		else
			precision = atoi(&prec[0]);

		//short or long?
		if(*p == 'h'){
			is_h = 1;
			*p++;
		}
		else if (*p == 'l'){
			is_l = 1;
			*p++;
		}

		switch(*p){
		case 'd':
			lval = va_arg(ap, long);
			if(is_h)
				printf("%d", (short)lval);
			else if (is_l)
				printf("%ld", lval);
			else
				printf("%d", (int)lval);
			break;
		case 'f':
			dval = va_arg(ap, double);
			printf("%f", dval);
			break;
		case 's':
			sval = va_arg(ap, char*);
			len = strlen(sval);
			if(precision == -1)
				precision = len;
			padding = min_width - precision;
			
			if(!left_adj) //we need to add padding before
			{
				while(padding-- > 0)
					putchar(' ');
			}
			for(;precision-- > 0; sval++)
				putchar(*sval);
			if(left_adj){
				while(padding-- > 0)
					putchar(' ');
			}
			break;
		default:
			putchar(*p);
			break;
		}
	}
	va_end(ap);
}

