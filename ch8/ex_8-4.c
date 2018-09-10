//compile: gcc ex_8-4.c
//run: ./a.out

/*Exercise 8-4: The standard library function 

	int fseek(FILE *fp, long offset, int origin)
 
   is identical to lseek except that fp is a file pointer instead of a file descriptor
   and the return value is an int status, not a position. Write fseek. Make sure that
   your fseek coordinates properly with the buffering done for the other functions of
   the library.		

*/
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#define PERMS 0666

enum _flags {
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
	int flag;
	int fd;
} _FILE;

_FILE _io_b[FOPEN_MAX] = {
	{0, (char *) 0, (char *) 0, _READ, 0},
	{0, (char *) 0, (char *) 0, _WRITE, 1},
	{0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2}
};

int fillbuf(_FILE *);
int flushbuf(int, _FILE *);
#define getC(p)	  (--(p)->cnt >= 0 \
				? (unsigned char) *(p)->ptr++ : fillbuf(p))
#define putC(x,p) (--(p)->cnt >= 0) \
				? *(p)->ptr++ = (x) : flushbuf((x),p)

int f_seek(_FILE *fp, long offset, int origin){

	return lseek(fp->fd, offset, origin) == -1 ? 0 : 1;
	
}


int f_flush(_FILE *fp){ //'to' is fd for _READ flagged
	_FILE *flush;
	int OK = 1;
	//if NULL is passed, flush all open output streams to their outputss
	if(fp == NULL){
		for(flush = _io_b; flush < _io_b + FOPEN_MAX; flush++)
		{	
			if(flush->flag&_WRITE && (OK = f_flush(flush)))
				;
			if(!OK){
				printf("error flushing buffer %d\n", flush->fd);
				return 0;
			}
		}
		return 1;
	}

	//check if the buffer has been freed
	if(fp->base == NULL){
		printf("error: fflush passed invalid buffer\n");
		return 0;
	}
	if(fp->flag&_WRITE){
		write(fp->fd, fp->base, fp->ptr - fp->base); //flush _WRITEs by writing to their outputs
	}
	fp->ptr = fp->base; //reset, don't free.
	return 1;
	
}

void f_close(_FILE *fp){
	free((void*)fp->base);
	fp->flag = 0;	
}


_FILE *f_open(char *name, char *mode){
	int fd;
	_FILE *fp;

	if(*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;
	for(fp = _io_b; fp < _io_b + FOPEN_MAX; fp++)
		if((fp->flag & (_READ | _WRITE)) == 0)
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
	fp->base = NULL;
	fp->flag = (*mode == 'r') ? _READ : _WRITE;
	fp->cnt = 0;	
	return fp;
}

int fillbuf(_FILE *fp){
	int bufsize;

	if((fp->flag&(_READ|_EOF|_ERR)) != _READ)
		return EOF;
	bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
	if(fp->base == NULL)
		if((fp->base = (char *) malloc(bufsize)) == NULL)
			return EOF;
	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);
	if(--fp->cnt < 0){
		if(fp->cnt == -1)
			fp->flag |= _EOF;
		else
			fp->flag |= _ERR;
		fp->cnt = 0;
		return EOF;
	}

	return (unsigned char) *fp->ptr++;
}
int flushbuf(int c, _FILE *fp){
	//check if the pointer passed has an error or isn't a write
	if((fp->flag&(_WRITE|_ERR|_EOF)) != _WRITE)
		return EOF;
	int bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
	if(fp->base == NULL){
		if((fp->base = (char *) malloc(bufsize)) == NULL)
			return EOF;
	}
	else {
		f_flush(fp);
	}
	fp->ptr = fp->base;
	fp->cnt = bufsize;
	putC(c, fp);
}

int main(){
	int c;
	_FILE *infile = f_open("somefile", "r");
	_FILE *outfile = f_open("anotherfile", "w");
	int sook = f_seek(infile, 3L, 0);
	printf("%d", sook);	
	while((c = getC(infile)) != EOF)
		putC(c, outfile);
	flushbuf(c, outfile);
	f_close(infile);
	f_close(outfile);
}
