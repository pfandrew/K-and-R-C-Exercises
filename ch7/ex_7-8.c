//compile: gcc ex_7-8.c -o flist
//run: ./flist file1 file2 ...

#include <stdio.h>

#define MAXFILES 10
#define FNAMESTART 1

void printpage(FILE *, char *, int);

int main(int argc, char *argv[]){
	FILE *fpa[MAXFILES];
	int i;
	if(argc < 2)
		printf("usage: flist filename filename ... \n");
	else{
		if(argc > FNAMESTART + MAXFILES)
			printf("max files exceeded. listing only first %d", MAXFILES);
		for(i = 0; i < MAXFILES && argc-- > FNAMESTART; i++){
			fpa[i] = fopen(argv[i + FNAMESTART], "r");
			printpage(fpa[i], argv[i + FNAMESTART], i + 1);
			fclose(fpa[i]);
		}
	}

}

void printpage(FILE *fp, char *filename, int page){
	int c;
	printf("\n|///////////////////////////////////////////////////|\n");
	printf("| %s\t\t\t\t\t\t(%d) |\n", filename, page);
	printf("|///////////////////////////////////////////////////|\n");
	while((c = getc(fp)) != EOF)
		putchar(c);
}
