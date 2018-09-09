//compile: gcc ex_8-2.c
//run: ./a.out

//Exercise 8-2: Rewrite fopen and _fillbuf with fields instead of explicit bit operation. Compare code size and execution speed.

/*note - on my machine, this version using fields wrote 10000000 characters of a 
file to stdout in .114 ms. 

The program using flags and bit operations wrote the same file in .109 ms.

So this program's code is larger, and it is slightly slower.
*/
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#define PERMS 0666

enum _flags { //for 
	_READ = 01,
	_WRITE = 02,
	_UNBUF = 04,
	_EOF = 010,
	_ERR = 020
};

typedef struct _io_buf {
	int cnt;
	char *ptr;
	char *base;
	unsigned int _READ : 1;
	unsigned int _WRITE : 1;
	unsigned int _UNBUF : 1;
	unsigned int _EOF : 1;
	unsigned int _ERR : 1;
	int fd;
} _FILE;

_FILE _io_b[FOPEN_MAX] = {
	{0, (char *) 0, (char *) 0, 1,0,0,0,0, 0},
	{0, (char *) 0, (char *) 0, 0,1,0,0,0, 1},
	{0, (char *) 0, (char *) 0, 0,1,1,0,0, 2}
};


_FILE *f_open(char *name, char *mode){
	int fd;
	_FILE *fp;
	
	if(*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;
	for(fp = _io_b; fp < _io_b + FOPEN_MAX; fp++)
		if(fp->_READ == 0 && fp->_WRITE == 0)
			break;
	if(fp >= _io_b + FOPEN_MAX)
		return NULL;
	
	if(*mode == 'w')
		fd = creat(name, PERMS);
	else if (*mode == 'a'){
		if((fd = open(name, O_WRONLY, 0)) == -1)
			fd = creat(name, PERMS);
		lseek(fd, 0L, 2);
	}
	else
		fd = open(name, O_RDONLY, 0);

	if(fd == -1)
		return NULL;
	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;
	if(*mode == 'r')
		fp->_READ = 1; 
	else
		fp->_WRITE = 1;
	return fp;
}

int fillbuf(_FILE *fp){
	int bufsize;

	if(fp->_READ && (fp->_ERR || fp->_EOF))
		return EOF;
	if(fp->_UNBUF == 1)
		bufsize = 1; 
	else
		bufsize = BUFSIZ;
	if(fp->base == NULL)
		if((fp->base = (char *) malloc(bufsize)) == NULL)
			return EOF;
	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);
	if(--fp->cnt < 0){
		if(fp->cnt == -1)
			fp->_EOF = 1;
		else
			fp->_ERR = 1;
		fp->cnt = 0;
		return EOF;
	}

	return (unsigned char) *fp->ptr++;
}

int main(){
	int c;
	_FILE *myfile = f_open("somefile", "r");
	if(myfile == NULL){
		printf("could not open file\n");
		return 0;
	}
	while((c = fillbuf(myfile)) != EOF){
		printf("%c", c);
		while(myfile->cnt-- > 0)
			printf("%c", *myfile->ptr++);
	}
}
