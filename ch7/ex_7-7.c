//compile: gcc ex_7-7.c -o pfind
//run: ./pfind [pattern] [file1, file2, ... file5]

//Exercise 7-7: Modify the pattern finding program of Chapter 5 to take its input from a set of named files or, if no files are named as arguments, from the standard input. Should the file name be printed when a matching line is found?

#include <stdio.h>
#include <string.h>

#define MAXLINE 1000
#define MAXFILES 5

int get_line(char *, int, FILE *);

int main(int argc, char *argv[]){
	char line[MAXLINE];
	int found = 0, files, i = 0;
	FILE *fpa[MAXFILES];
	if(argc < 2){
		printf("usage: pfind [phrase] [file1, file2, ... file5]");
		return 0;
	}
	else if(argc == 2){
		fpa[i++] = stdin;
	}
	else if(argc > 2){
		if(argc > 2 + MAXFILES)
			printf("max files exceeded. only searching first %d...", MAXFILES);
		for(i = 0; argc-- > 2 && i < MAXFILES; i++){
			fpa[i] = fopen(argv[2 + i], "r");
		}
	}
	files = i;
	for(i = 0; i < files; i++){
		int line_no = 1;
		while(get_line(line, MAXLINE, fpa[i]) > 0){
			if(strstr(line, argv[1]) != NULL)
				printf("%s:%d:%s", fpa[i] == stdin ? "stdin" : argv[i + 2], line_no, line);
			line_no++;
		}
		if(fpa[i] != stdin)
			fclose(fpa[i]);
	}

	

	return 1;
}

int get_line(char *s, int maxline, FILE *fp){
	if(fgets(s, maxline, fp) == NULL)
		return 0;
	else
		return strlen(s);
}
