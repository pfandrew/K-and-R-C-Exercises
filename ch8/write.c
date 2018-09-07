//program from section 8.2; copies input to output

//on mac no header necessary to have access to read/write

#define BUFSIZ 1000

int main(){
	char buf[BUFSIZ];
	int n;

	while((n= read(0, buf, BUFSIZ)) > 0)
		write(1, buf, n);
	return 0;
}
