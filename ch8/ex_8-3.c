//compile: gcc ex_8-3.c
//run: ./a.out

//Exercise 8-3: Design and write _flushbuf, fflush, and fclose.

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

/*
	_READ pointers have a cnt that tells them how many are left in the buffer
	_WRITE pointers have a cnt that tells them how many they have left to fill up

	as chars are removed from _READ pointer buffers with getc, the cnt goes down
	as chars are added to _WRITE pointer buffers with putc, the cnt goes down

	this leads to confusion, because we assume that adding and removing chars
	should move the cnt up or down respectively

	but in this case, the cnt always goes down for both types of pointers, though
	the accompanying actions of adding and removing characters are opposite
*/

/* from man7.org:
 For output streams, fflush() forces a write of all user-space
 buffered data for the given output or update stream via the stream's
 underlying write function.

 For input streams associated with seekable files (e.g., disk files,
 but not pipes or terminals), fflush() discards any buffered data that
 has been fetched from the underlying file, but has not been consumed
 by the application.

 The open status of the stream is unaffected.

 If the stream argument is NULL, fflush() flushes all open output
 streams.

 For a nonlocking counterpart, see unlocked_stdio(3)
*/
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
	while((c = getC(infile)) != EOF)
		putC(c, outfile);
	flushbuf(c, outfile);
	f_close(infile);
	f_close(outfile);
}
