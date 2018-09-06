//compile: gcc ex_7-6.c -o fcmp
//run: ./fcmp [filename] [filename]

//Exercise 7-6: Write a program to compare two files, printing the first line where they differ.

#include <stdio.h>
#define MAXLINE 10000
int comparefiles(char *, char *);

int main(int argc, char *argv[]){
	if(argc != 3){
		printf("usage: fcmp [filename] [filename]\n");
		return 0;
	}
	
	int r = comparefiles(argv[1], argv[2]);

	return r;
}

int comparefiles(char *f1, char *f2){
	FILE *fp1 = fopen(f1, "r");
	FILE *fp2 = fopen(f2, "r");
	int c, d, i = 0;
	char line[MAXLINE];
	while(((c = getc(fp1)) == (d = getc(fp2))) && c != EOF && d != EOF)	{
		if(c == '\n'){
			i = 0;
			line[i] = '\0';
		}
		else{
			line[i++] = c;
		}
	}

	if(c != d){
		while(c != EOF && c != '\n'){
			line[i++] = c;
			c = getc(fp1);
		}
	}

	line[i] = '\0';
	printf("%s\n", line);

	fclose(fp1);
	fclose(fp2);	
}
