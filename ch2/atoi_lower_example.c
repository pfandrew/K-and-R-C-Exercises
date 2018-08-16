//functions from section 2.7; atoi  converts string of numbers to an integer
//lower converts c to lower case, ASCII only

#include <stdio.h>
#define MAX 1000
int atoi(char s[]){
	int i, n;
	n = 0;
	for(i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
		n = 10*n + (s[i] - '0');
	return n;
}

int lower(int c){
	if(c >= 'A' && c <= 'Z')
		return c + 'a' - 'A';
	else
		return c;
}

int main(){
	int i, c;
	i = 0;
	char input[MAX];

	//testing atoi()
	printf("Enter a number: ");
	while(i < MAX - 1 && (c = getchar()) != '\n')
		input[i++] = c;
	input[i] = '\0';
	printf("After atoi: %d\n\n", atoi(input));

	//testing lower()
	i = 0;
	printf("Enter a string with some upper-case leetters: ");
	while(i < MAX - 1 && (c = getchar()) != '\n' && c != EOF)
		input[i++] = lower(c);
	input[i] = '\0';
	printf("After lower(): %s\n", input);
}
