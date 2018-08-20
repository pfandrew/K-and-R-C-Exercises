//from section 3.5; shell sort implementation

#include <stdio.h>
#include <ctype.h>

#define MAX 1000
void shellsort(int v[], int n){
	int gap, i, j, temp;

	for(gap = n/2; gap > 0; gap /= 2){
		for(i = gap; i < n; i++){
			for(j = i - gap; j >= 0 && v[j] > v[j + gap]; j -= gap){
				temp = v[j];
				v[j] = v[j + gap];
				v[j + gap] = temp;
			}
		}
	}
}

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
	int c, i, k;
	i = k = 0;
	char input[MAX];
	int nums[MAX];
	//enter numbers hitting Enter key after each number; end loop with Ctrl-D (Mac)
	while(k < MAX - 1 && (c = getchar()) != EOF){
		if(c == '\n')
		{
			input[i] = '\0';
			nums[k++] = s_atoi(input);
			i = 0;
		}
		else 
		{
			if(i < MAX - 1){
				input[i++] = c;
			}
			else {
				input[i] = '\0';
				nums[k++] = s_atoi(input);
				i = 0;
			}
		}
	}

	shellsort(nums, k);
	for(i = 0; i < k; i++)
		printf(" %d", nums[i]);

	printf("\n");

}
