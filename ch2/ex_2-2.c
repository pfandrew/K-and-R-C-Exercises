//compile: gcc ex_2-1.c
//run: ./a.out

//Exercise 2-1: Write a loop equivalent to the for loop above without using && or ||.

#define MAX 1000

int main(){
	/*original:
		for(i = 0; i < lim - 1 && (c=getchar()) != '\n' && c != EOF; i++)
			s[i] = c;
	*/

	char s[MAX];
	int i, c;
	i = 0;
	//technically 'break' has not been introduced yet in the book, but that would be easier.
	c = getchar();
	while(c != '\n'){
		if(i >= MAX - 1)
			c = '\n';
		else if(c == -1)
			c = '\n';
		else{
			s[i] = c;
			c = getchar();
			++i;
		}	
	}
	s[i] = '\0';
	printf("%s", s);
}
