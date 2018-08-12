//compile: gcc ex_1-23.c
//run: ./a.out

//Exercise 1-23: Write a program to remove all comments from a C program. Don't forget to handle quoted strings and character constants properly. C comments do not nest.

#include <stdio.h>

#define IN 1
#define OUT 0
#define DQ '\"'
#define SQ '\''
#define MAX_PROGRAM_LENGTH 1000

int main(){

	int c, i, k, last, c_state, q_state;
	c_state = q_state = i = OUT;
	char program_in[MAX_PROGRAM_LENGTH];
	char program_out[MAX_PROGRAM_LENGTH];
	char q_type = DQ;

	//take in program line by line, and show it back to user
	while(i < MAX_PROGRAM_LENGTH - 1 && (c = getchar()) != EOF){
		program_in[i] = c;
		++i;
	}
	program_in[i] = '\0';
	printf("\n\n//ORIGINAL PROGRAM: \n%s\n", program_in);


	//remove comments and output
	i = k = 0;
	while((c = program_in[i]) != '\0'){
		//switch to quote state
		if(c == '\"' || c == '\''){
			q_state = IN;
			q_type = c;
			program_out[k++] = c;
			++i;
		}

		//print everything between quotes, until we reach the close quote of the same type
		else if(q_state){
			while( ((last = c) == '\\') || ((c = program_in[++i]) != q_type)) {
				program_out[k++] = last;
			}
			q_state = OUT;
			program_out[k++] = last;
			program_out[k++] = c;
			++i;
		}
		
		//remove //-style comments		
		else if((last = c) == '/' && (c = program_in[++i]) == '/'){
			c_state = IN;
			while(c_state){
				c = program_in[++i];
				if(c == '\n'){
					c_state = OUT;
					program_out[k++] = c;
				}
			}
		}
		
		else if(last == '/' && c == '*'){
			c_state = IN;
			last = program_in[++i];
			c = program_in[++i];
			while(c_state){
				if(last == '*' && c == '/'){
					c_state = OUT;
				}
				else
				{
					last = c;
					c = program_in[++i];
				}
			}
		}
		else{
			program_out[k++] = c;
			++i;
		}
	}
	program_out[k] = '\0';	
	printf("\n\n//PROGRAM WITHOUT COMMENTS:\n%s", program_out);
	
	return 0;
}


