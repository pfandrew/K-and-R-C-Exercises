//from section 3.5
//function atoi converts s to an integer; version 2

#include <stdio.h>
#include <ctype.h>
#define MAX 1000
int s_atoi(char s[]){
	int i, n, sign;

	for(i = 0; isspace(s[i]); i++)
		;

	sign = (s[i] == '-') ? -1 : 1;
	if(s[i] == '+' || s[i] == '-')
		i++;
	for(n = 0; isdigit(s[i]); i++)
		n = 10 * n + (s[i] - '0');

	return sign * n;
}

int main(){
	int c, i;
	char input[MAX];
	i = 0;
	while(i < MAX - 1 && (c = getchar()) != EOF){
		input[i++] = c;
	}
	input[i] = '\0';
	printf("%d\n", s_atoi(input));
}
