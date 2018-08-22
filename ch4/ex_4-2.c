//compile: gcc ex_4-2.c
//run: ./a.out

/*Exercise 4-2: Extend atof to handle scientific notation of the form 
	123.45e-6
Where a floating-point number may be followed by e or E and an optional signed exponent.*/

#include <stdio.h>
#include <ctype.h>

double atof(char s[]){
	double val, power;
	int i, sign, exp_sign, exp_num = 0;

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
	if((s[i] == 'e' || s[i] == 'E') && s[i++]){
		exp_sign = s[i] == '-' ? -1 : 1;
		if((s[i] == '+' || s[i] == '-') && s[i++])
			;
		//calculate number for exp
		while(isdigit(s[i])){
			exp_num = 10 * exp_num + (s[i] - '0');
			i++;
		}
		printf("%d", exp_num);
		//calculate exp value
		while(exp_num-- > 0){
			power = exp_sign == 1 ? power / 10.0 : power * 10.0;
		}
		
	}

	return sign * val / power;
}

int main(){
	char d1[] = "+76.900e6";
	char d2[] = "-7635.000e-3";
	char d3[] = "8739.987329E+2";

	printf("%f\n%f\n%f\n", atof(d1), atof(d2), atof(d3));
}
