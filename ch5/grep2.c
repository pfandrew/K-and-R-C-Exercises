//rudimentary grep from section 4.1, rewritten in section 5.10
#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int get_line(char *line, int max);

int main(int argc, char *argv[]){
	char line[MAXLINE];
	int found = 0;

	if(argc != 2){
		printf("Usage: find pattern\n");
	}
	else{
		while(get_line(line, MAXLINE) > 0){
			if(strstr(line, argv[1]) != NULL){
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
	c == EOF ? return -1 : return i;
}
