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

_DIR *open_dir(char *dirname);
Dirent *read_dir(_DIR *dfd);
void close_dir(_DIR *dfd);


