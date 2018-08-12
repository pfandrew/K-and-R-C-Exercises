//compile: gcc ex_1-24.c
//run: ./a.out

//Exercise 1-24: Write a program to check a C program for rudimentary syntax errors like unbalanced parentheses, brackets and braces. Don't forget about quotes, both single and double, escape sequences, and comments. (This program is hard if you do it in full generality.)

#include <stdio.h>

#define NUM_ES 	12

#define IN 1
#define OUT 0

#define SQ 		'\''
#define DQ 		'\"'
#define LB 		'{'
#define RB 		'}'
#define LP 		'('
#define RP 		')'
#define LA 		'['
#define RA 		']'
#define t_LC 	'l'
#define t_RC 	'r'
#define es_s	'\\'
#define OVERLAP 'o'

#define MAX_PROGRAM_LENGTH 1000
#define ERROR_STR_LEN 1000

void report_error(char type, int line)
{
	if(type == LB || type == RB || type == LP || type == RP || type == LA || type == RA)
		printf("ERROR: unmatched %c on line %d\n", type, line);
	else if(type == t_LC || type == t_RC)
		printf("ERROR: unmatched comment on line %d\n", line);
	else if(type == SQ || type == DQ)
		printf("ERROR: unmatched %c on line %d\n", type, line);
	else if(type == es_s)
		printf("Escape slash %c without qualifier on line %d\n", type, line);
	else if(type == OVERLAP)
		printf("Overlapping on line %d ", line);
	else
		printf("Unknown ERROR called on line %d", line);
}

int main(){
	int c, i, k, line, last, mlc_state, slc_state, sq_state, dq_state, es_state;
	int braces = OUT, brackets = OUT, parentheses = OUT;
	int last_lp = 0, last_lc = 0, last_la = 0, last_lb = 0, last_dq = 0, last_sq = 0;
	i = mlc_state = slc_state = sq_state = dq_state = es_state = OUT;
	line = 1;
	int sq = 0, dq = 0, lb = 0, rb = 0, lp = 0, rp = 0, la = 0, ra = 0, lc = 0, rc = 0, es = 0;

	char program_in[MAX_PROGRAM_LENGTH];

	printf("Enter C Program Below, followed by EOF (Ctrl-D on Mac)\n");

	//take in program
	while(i < MAX_PROGRAM_LENGTH - 1 && (c = getchar()) != EOF){
		program_in[i++] = c;
	}
	program_in[i] = '\0';

	i = 0;
	c = 1;
	while((c = program_in[i++]) != '\0'){
		switch(c){
			case '\n':
				if(mlc_state || dq_state)
					break;
				if(es_state) report_error(es_s, line); es_state = OUT;
				++line;
				slc_state = OUT;
				break;
			case DQ:
				if(es_state) report_error(es_s, line); es_state = OUT;
				if(mlc_state || slc_state || sq_state || es_state){
					break;
				}
				else if(dq_state)
					dq_state = OUT;
				else
					dq_state = IN;
				++dq;
				last_dq = line;
				break;

			case SQ:
				if(es_state) report_error(es_s, line); es_state = OUT;
				if(mlc_state || slc_state || dq_state || es_state){
					break;
				}
				else if(sq_state)
					sq_state = OUT;
				else
					sq_state = IN;
				++sq;
				last_sq = line;
				break;

			case LB:
				if(es_state) report_error(es_s, line); es_state = OUT;
				if(mlc_state || slc_state || dq_state || sq_state)  
					break;
				else
					++lb;
				last_lb = line;
				break;

			case RB: 
				if(es_state) report_error(es_s, line); es_state = OUT;
				if(mlc_state || slc_state ||  dq_state || sq_state)
					break;
				else
					++rb;
 
				if(rb > lb) 
					report_error(LB, line); 
				break;
				
			case LP: 
				if(es_state) report_error(es_s, line); es_state = OUT;
				if(mlc_state || slc_state || dq_state || sq_state)
					break;
				else 
					++lp;
				last_lp = line;
				break;
			case RP: 
				if(es_state) report_error(es_s, line); es_state = OUT;
				if(mlc_state || slc_state || dq_state || sq_state)
					break;
				else	
					++rp;

				if(rp > lp)
					report_error(RP, line);
				break;

			case LA: 
				if(es_state) report_error(es_s, line); es_state = OUT;
				if(mlc_state || slc_state || dq_state || sq_state)
					break;
				else
					++la; 
				last_la = line;
				break;
			case RA: 
				if(es_state) report_error(es_s, line); es_state = OUT;
				if(mlc_state || slc_state || dq_state || sq_state)
					break;
				else
					++ra;
				if(ra > la)
					report_error(RA, line);
				break;

			case es_s:
				if(mlc_state || slc_state || dq_state || sq_state || es_state)
				{	
					es_state = OUT;	
					break;
				}
				else if(!es_state)
					es_state = IN;
				break;
				
			case 'a': es_state = OUT; break;
			case 'b': es_state = OUT; break;
			case 'f': es_state = OUT; break;
			case 'n': es_state = OUT; break;
			case 'r': es_state = OUT; break;
			case 't': es_state = OUT; break;
			case 'v': es_state = OUT; break;
			case 's': es_state = OUT; break;
			case 'q': es_state = OUT; break;
			case 'e': es_state = OUT; break;
			case '?': es_state = OUT; break;
			case '*':
				if(es_state) report_error(es_s, line); es_state = OUT;
				if(sq_state || dq_state || sq_state)
					break;
				else if(mlc_state)
				{
					if((c = program_in[++i]) == '/')
						mlc_state = OUT;
						rc++;
						if(rc > lc)
							report_error(t_RC, line);
				}
				else if(last == '/'){
					mlc_state = IN;
					c = program_in[++i];
					++lc;
					last_lc = line;
				}
				break; 
			case '/':
				if(es_state) report_error(es_s, line); es_state = OUT;
				if(mlc_state || slc_state){
					if(last == '*'){
						mlc_state = OUT;
						++rc;
						if(rc > lc){
							report_error(t_RC, line);
						}
					}
					break;
				}
				else if(last == '/')
					slc_state = IN;
				break;
			default: 
				if(es_state){
					report_error(es_s, line);
					es_state = OUT;
				}
				break;
		}//switch
	last = c;
	}//while
	if(lp > rp)
		report_error(LP, last_lp);			
	if(lb > rb)
		report_error(LB, last_lb);				
	if(la > ra)
		report_error(LA, last_la);				
	if(lc > rc)
		report_error(t_LC, last_lc);				
	if(sq / 2 != (int)((float)dq / 2))
		report_error(SQ, last_sq);
	if(dq / 2 != (int)((float)dq / 2))
		report_error(DQ, last_dq);
		
	return 0;
} //main

