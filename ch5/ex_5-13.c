//compile: gcc ex_5-13.c -o tail
//run: tail -n

/*Exercise 5-13: Write the program tail, which prints the last n lines of its input. By default, n is 10, let us say, 
but it can be changed by an optional argument, so that

	tail -n

prints the last n lines. The program should behave rationally no matter how unreasonable the input or the value of n. 
Write the program so it makes the best use of available storage; lines should be stored as in the sorting program of 
Section 5.6, not in a two-dimensional array of fixed size.
*/

#include <stdio.h>
#include <ctype.h>

#define ALLOCSIZE 10000
#define MAXLINE 100
#define MAXLINES 100

int get_line(char *line, int maxline, char buf[]);
char *str_cpy(char buf[], char line[]);
void writelines(char *lineptr[], int begin, int end);

int main(int argc, char *argv[]){
	int lines = 0, accept = 1, d;
	
	//grab number from argument
	if(argc < 2){
		printf("usage: tail -n\n");
		return 0;
	}
	if(**++argv == '-'){
		while((d = *++*argv) != '\0' && accept){
			if(isdigit(d)){
				lines = (lines * 10) + (d - '0');
			}
			else
				accept = 0;
		}
	}
	else
		accept = 0;
	if(!accept){
		printf("usage: tail -n\n");		
		return 0;
	}

	char *lineptr[MAXLINES];
	static char buf[ALLOCSIZE];
	static int buf_i;
	char line[MAXLINE];
	int space = 1, line_no = 0, len;

	//begin input
	while((len = get_line(line, MAXLINE, buf)) > 0 && space){
		if(buf_i + len < ALLOCSIZE){
			lineptr[line_no++] = str_cpy(&buf[buf_i], line);
			buf_i += len + 1;
		}
		else{
			space = 0;
			printf("error: no space remaining for '%s'\nexiting...\n", line);
		}
	}
	if(lines == line_no || lines > line_no){
		writelines(lineptr, 0, line_no);
	}
	else if(lines < line_no)
		writelines(lineptr, line_no - lines, line_no);

	return 1;
}

void writelines(char *lineptr[], int begin, int end){
	for(int i = begin; i < end; i++)
		printf("%s", lineptr[i]);
}

int get_line(char s[], int maxline, char buf[]){
	int c, i = 0;
	while(i < maxline - 1 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;
	if(c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

char *str_cpy(char d[], char s[]){
	char *r = d;
	while(*s != '\0')
		*d++ = *s++;
	*d = *s;
	return r;
}
