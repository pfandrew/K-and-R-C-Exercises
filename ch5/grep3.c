//program from section 5.10; now can use options -n and -x for line number and to print all lines except for those with pattern0
#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int get_line(char *line, int max);

int main(int argc, char *argv[]){
	char line[MAXLINE];
	long lineno = 0;
	int c, except = 0, number = 0, found = 0;

	//parse options
	while(--argc > 0 && (*++argv)[0] == '-'){
		while(c = *++argv[0]){
			switch(c){
				case 'x':
					except = 1;
					break;
				case 'n':
					number = 1;
					break;
				default:
					printf("find: illegal option %c\n", c);
					argc = 0;
					found = -1;
					break;
			}
		}
	}

	if(argc != 1){
		printf("Usage: find -x -n pattern\n");
	}
	else{
		while(get_line(line, MAXLINE) > 0){
			lineno++;
			if((strstr(line, *argv) != NULL) != except){
				if(number)
					printf("%ld:", lineno);
				printf("%s", line);
				found++;
			}
		}
	}
	return found;
}

int get_line(char *s, int maxline){
	int i, c;
	for(i = 0; i < maxline - 1 && (c = getchar()) != EOF && c != '\n'; i++)
		*s++ = c;
	if(c == '\n' && i < maxline - 1){
		*s++ = c;
		i++;
	}
	*s = '\0';
	if(c == EOF)
		return -1;
	else
		return i;
}
