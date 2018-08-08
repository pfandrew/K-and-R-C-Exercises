//compile: gcc ex_1-2.c
//run: ./a.out

//Exercise 1-2: Experiment to find out what happens when printf's argument string contains \c, where c is some character not listed above.

int main(){
	printf("\\g: \g\n");
	printf("\\h: \h\n");
	printf("\\z: \z\n");
	return 0;
}
