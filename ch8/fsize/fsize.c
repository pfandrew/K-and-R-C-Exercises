//program from chapter 8.6; special form of ls
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/_types/_s_ifmt.h>
#include <sys/types.h>
#include "dirent.h"
#include <sys/dir.h>
#include <sys/stat.h>
#include <errno.h>
#define MAX_PATH 1024

//NOTE: on my mac one encounters errors when using read() on a directory fd. 
//one is not allowed to use read() when the file descriptor refers to a directory. 
//the call: read(dp->fd, (char *) &dirbuf, sizeof(dirbuf)) returns -1, with error
//"is a directory". so it would appear that using system implemented readdir is required.

void f_size(char *);
void dir_walk(char *, void (*fcn)(char *));

int main(int argc, char **argv){
	if(argc == 1)
		f_size(".");
	else
		while(--argc > 0)
			f_size(*++argv);
	return 0;
}

void f_size(char *name){
	struct stat stbuf;
	
	if(stat(name, &stbuf) == -1){
		fprintf(stderr, "fsize: can't access %s\n", name);
		return;
	}
	if(S_ISDIR(stbuf.st_mode)){ //S_ISDIR defined in sys/stat.h
		dir_walk(name, f_size);
	}
	printf("%8ld %s\n", stbuf.st_size, name);
}

void dir_walk(char *dir, void (*fcn)(char *)){
	char name[MAX_PATH];
	Dirent *dp;
	_DIR *dfd;

	if((dfd = open_dir(dir)) == NULL){
		fprintf(stderr, "dirwalk: can't open %s\n", dir);
		return;
	}	

	while((dp = read_dir(dfd)) != NULL){
		
		if(strcmp(dp->name, ".") == 0 || strcmp(dp->name, "..") == 0)
		{
			continue;
		}
		if(strlen(dir) + strlen(dp->name) > sizeof(name)){
			fprintf(stderr, "dirwalk: name %s/%s too long\n", dir, dp->name);
		}
		else{
			sprintf(name, "%s/%s", dir, dp->name);
			(*fcn)(name);
		}

	}
	close_dir(dfd);
}

_DIR *open_dir(char *dirname){
	int fd;
	struct stat stbuf;
	_DIR *dp;

	if((fd = open(dirname, O_RDONLY, 0)) == -1 ||fstat(fd, &stbuf) == -1 || (stbuf.st_mode & S_IFMT) != S_IFDIR || (dp = (_DIR *) malloc(sizeof(_DIR))) == NULL){
			return NULL;
	}
	dp->fd = fd;
	return dp;
}


void close_dir(_DIR *dp){
	if(dp){
		close(dp->fd);
		free(dp);
	}
}

Dirent *read_dir(_DIR *dp){
	struct direct dirbuf;
	static Dirent d;
	while(read(dp->fd, (char*) &dirbuf, sizeof(dirbuf)) == sizeof(dirbuf)){
		if(dirbuf.d_ino == 0){
			continue;
		}
		d.ino = dirbuf.d_ino;
		strncpy(d.name, dirbuf.d_name, NAME_MAX);
		d.name[NAME_MAX] = '\0';
		printf("HERE");
		return &d;
	}
	int e = errno;
	printf("%s", strerror(e));
	return NULL;
}
