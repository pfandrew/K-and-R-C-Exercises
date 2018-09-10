//program from chapter 8.6; special form of ls
#define NAME_MAX 14

typedef struct {
	long ino;
	char name[NAME_MAX + 1];
} Dirent;

typedef struct {
	int fd;
	Dirent d;
} _DIR;

_DIR *opendir(char *dirname);
Dirent *readdir(_DIR *dfd);
void closedir(DIR *dfd);


