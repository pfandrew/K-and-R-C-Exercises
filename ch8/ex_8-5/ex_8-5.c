//compile: gcc ex_8-5.c
//run: ./a.out

//Exercise 8-5:

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

//NOTE - my OS requires a call to read(). thus the function read_dir from the book is useless, so it has been replaced
//prints name, size, blocks, blocksize, permissions of inode


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
	char perm_string[10] = {'\0'};
	char perm_chars[3] = {'x', 'w', 'r'};
	if(stat(name, &stbuf) == -1){
		fprintf(stderr, "fsize: can't access %s\n", name);
		return;
	}
	if(S_ISDIR(stbuf.st_mode)){ //S_ISDIR defined in sys/stat.h
		dir_walk(name, f_size);
	}
	int mode = stbuf.st_mode;
	for(int i = 0; i < 9; mode = mode >> 1, i++)
	{
		if(mode&1){
			perm_string[8-i] = perm_chars[i%3];
		}
		else
			perm_string[8-i] = '-';
	}
	perm_string[9] = '\0';
	
	printf("%-10s%8ld %4ld %8ld %s\n", perm_string, stbuf.st_size, stbuf.st_blocks, stbuf.st_blksize, name);
}

void dir_walk(char *dir, void (*fcn)(char *)){
	char name[MAX_PATH];
	struct dirent *dp;
	DIR *dfd;
	Dirent file_data;
	if((dfd = opendir(dir)) == NULL){
		fprintf(stderr, "dirwalk: can't open %s\n", dir);
		return;
	}	

	while((dp = readdir(dfd)) != NULL){
		if(strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
		{
			continue;
		}
		file_data.ino = dp->d_ino;
		strncpy(file_data.name, dp->d_name, NAME_MAX);
		if(strlen(dir) + strlen(file_data.name) > sizeof(name)){
			fprintf(stderr, "dirwalk: name %s/%s too long\n", dir, dp->d_name);
		}
		else{
			sprintf(name, "%s/%s", dir, file_data.name);
			(*fcn)(name);
		}

	}
	
	closedir(dfd);
}



void close_dir(_DIR *dp){
	if(dp){
		close(dp->fd);
		free(dp);
	}
}

