//program from section 8.5; implements _fillbuf and fopen
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h> //malloc
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

_FILE _io_b[FOPEN_MAX] = { //mac has FOPEN_MAX
	{0, (char *) 0, (char *) 0, _READ, 0},
	{0, (char *) 0, (char *) 0, _WRITE, 1},
	{0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2}
};


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
	fp->cnt = 0;
	fp->base = NULL;
	fp->flag = (*mode == 'r') ? _READ : _WRITE;
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

int main(){
	int c;
	_FILE *myfile = f_open("somefile", "r");
	while((c = fillbuf(myfile)) != EOF){
		printf("%c", c);
		while(myfile->cnt-- > 0)
			printf("%c", *myfile->ptr++);
	}
}
