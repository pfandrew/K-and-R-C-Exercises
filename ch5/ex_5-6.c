//compile: gcc ex_5-6.c
//run: ./a.out

//Exercise 5-6: Rewrite appropriate programs from earlier chapters and exercises with pointers instead of array indexing. Good possibilities include getline (Chapters 1 and 4), atoi, itoa, and their variants (Chapters 2, 3, and 4), reverse (Chapter 3), and strindex and getop (Chapter 4).


int s_atoi(char* s){
	int i, n, sign;

	for(i = 0; isspace(*s); s++)
		;

	sign = (*s == '-') ? -1 : 1;
	if(*s == '+' || *s == '-')
		s++;
	for(n = 0; isdigit(*s); s++)
		n = 10 * n + (*s - '0');

	return sign * n;
}

void itoa(long int n, char* s){
	int i; 
	long int sign;

	if((sign = n) < 0)
		n = -n;

	i = 0;
	do {
		*s++ = n % 10 + '0';
	} while ((n /= 10) > 0);
	if(sign < 0)
		*s++ = '-';
	*s = '\0';
	reverse(s);
}

void reverse(char* s){
	char* i = s; 
	char* j = s + strlen(s) - 1; 
	char tmp;
	for(; i < j; i++, j--){
		tmp = *i, *i = *j, *j = tmp;
	}
}

int get_line(char* s, int lim)
{
	int c, i;
	i = 0;
	while(--lim > 0 && (c = getchar()) != EOF && c != '\n')
		*s++ = c;
	if(c == '\n')
		*s++ = c;
	*s = '\0';
	return i;
}

int str_index(char* s, char* t)
{
	char* j; 
	char* k;
	for(; *s != '\0'; s++){
		for(j = s, k = t; *k != '\0' && *j == *k; j++, k++)
			;
		if(k > t && *k == '\0')
			return 1;
	}
	return -1;
}

int getop(char* s){
	int i, c;

	while((*s = c = getch()) == ' ' || c == '\t')
		;
	*++s = '\0';
	if(!isdigit(c) && c != '.')
		return c;
	if(isdigit(c))
		while(isdigit(*++s = c = getch()))
			;
	if(c == '.')
		while(isdigit(*++s = c = getch()))
			;
	*s = '\0';
	if(c != EOF)
		ungetch(c);
	return NUMBER;
}
