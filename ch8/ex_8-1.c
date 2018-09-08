//compile: gcc ex_8-1.c -o fdcat
//run: time fdcat [filename]

//Exercise 8-1: Rewrite the program cat from Chapter 7 using read, write, open and close instead of their standard library equivalents. Perform experiments to determine the relative speeds of the two versions.

//NOTE: With the same three files input, this version beats the old version by a millisecond

#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
	
	int fd;
	void filecopy(int, int);	
	if(argc == 1)
		filecopy(0, 1);
	else {
		while(--argc > 0) {
			if((fd = open(*++argv, O_RDONLY, 0)) == -1) {
				printf("rcat: can't open %s\n", *argv);
				return 1;
			} else {
				filecopy(fd, 1);
				close(fd);
			}
		}
	}
	return 0;	
}

void filecopy(int in, int out){
	int c;
	while(read(in, &c, 1) > 0)
		write(out, &c, 1);
}
