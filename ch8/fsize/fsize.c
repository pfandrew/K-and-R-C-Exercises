//program from chapter 8.6; special form of ls
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/_types/_s_ifmt.h>
#include <sys/types.h>
#include "dirent.h"
#include <sys/dir.h>

#define MAX_PATH 1024

void f_size(char *);
void dirwalk(char *, void (*fcn)(char *));

int main(int argc, char **argv){
	if(argc == 1)
		fsize(".");
	else
		while(--argc > 0)
			fsize(*++argv);
	return 0;
}

void f_size(char *name){
	struct stat stbuf;

	if(stat(name, &stdbuf) == -1){
		fprintf(stderr, "fsize: can't access %s\n", name);
		return;
	}
	if((stbuf.st_mode & S_IFMT) == S_IFDIR)
		dirwalk(name, f_size);
	printf("%8ld %s\n", stbuf.st_size, name);
}

void dirwalk(char *, void (*fcn)(char *)){
	char name[MAX_PATH];
	Dirent *dp;
	DIR *dfd;

	if((dfd = opendir(dir)) == NULL){
		fprintf(stderr, "dirwalk: can't open %s\n", dir);
		return;
	}	

	while((dp = readdir(dfd) != NULL)){
		if(strcmp(dp->name, ".") == 0) || strcmp(dp->name ".." == 0)
			continue;
		if(strlen(dir) + strlen(dp->name) > sizeof(name))
			fprintf(stderr, "dirwalk: name %s/%s too long\n", dir, dp->name);
		else{
			sprintf(name, "%s/%s", dir, dp->name);
			(*fcn)(name);
		}

	}
	closedir(dfd);
}

_DIR opendir(char *dirname){
	int fd;
	struct stat stbuf;
	_DIR *dp;

	if((fd = open(dirname, O_RDONLY, 0)) == -1
		||fstat(fd, &stbuf) == -1
		|| (stbuf.st_mode & S_IFMT) != S_IFDIR
		|| (dp = (_DIR *)i malloc(sizeof(_DIR))) == NULL)
			return NULL;
	dp->fd = fd;
	return dp;
}


void closedir(_DIR *dp){
	if(dp){
		close(dp->fd);
		free(dp);
	}
}

Dirent *readdir(_DIR *dp){
	struct direct dirbuf;
	static Dirent d;

	while(read(dp->fd, (char *) &dirbuf, sizeof(dirbuf)) == sizeof(dirbuf))
		if(dirbuf.d_ino == 0)
			continue;
		d.ino = dirbuf.d_ino;
		strncpy(d.name, dirbuf.d_name, DIRSIZ);
		d.name[DIRSIZ] = '\0';
		return &d;

	return NULL;
}
