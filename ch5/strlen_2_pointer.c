//function from 5.4; strlen rewritten with two pointers
#include <stdio.h>
int str_len(char* s){
	char* p = s;
	while(*p != '\0')
		p++;
	return p - s;
}

/*
index|0123456  7 |
str  |HELLO W \0 |
     |s        p |
   strlen = p - s
*/

int main(){
	char* hw = "HELLO W";
	printf("Length of '%s': %d\n", hw, str_len(hw));	
}
