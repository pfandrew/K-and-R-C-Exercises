//function example from section 8.4; reads n bytes from a file at any arbitrary location

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#define MAXFN 1000

int get(int, long, char *, int);

int main(int argc, char *argv[]){
	int loc, fd, amt;
	char filename[MAXFN];
	char buf[BUFSIZ];
	if(argc < 4){
		printf("usage: rnbff [filename] loc amt\n");
		return 1;
	}
	else {
		strcpy(filename, argv[1]);
		loc = atoi(argv[2]);
		amt = atoi(argv[3]);
		fd = open(filename, O_RDONLY, 0);

		if(!loc || !amt || fd == -1){
			printf("usage: rnbff [filename] loc amt\n");
			return 0;
		}

		loc = get(fd, loc, buf, amt);

		if(loc != -1)
			printf("%s\n", buf);
		else
			printf("unable to read from file\n");
	}
}

int get(int fd, long pos, char *buf, int n){
	if(lseek(fd, pos, 0) >= 0)
		return read(fd, buf, n);
	else
		return -1;
}
