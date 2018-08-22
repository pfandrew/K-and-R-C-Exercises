//from section 4.2; converts string double to double
#include <stdio.h>
#include <ctype.h>

double atof(char s[]){
	double val, power;
	int i, sign;

	for(i = 0; isspace(s[i]); i++)
		;

	sign = s[i] == '-' ? -1 : 1;
	if(s[i] == '+' || s[i] == '-')
		i++;

	for(val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if(s[i] == '.')
		i++;
	for(power = 1.0; isdigit(s[i]); i++){
		val = 10.0 * val + (s[i] - '0');
		power = power * 10.0;
	}

	return sign * val / power;
}

int main(){
	char d1[] = "+76.900";
	char d2[] = "-7635.000";
	char d3[] = "8739.987329";

	printf("%f\n%f\n%f\n", atof(d1), atof(d2), atof(d3));
}
