#include <stdio.h>
#include <math.h>

int pascal(int pos, int rows);
int coef(int pos, int power);
void format(int* equ, int len);

int main(int argc, char** argv) {
	int n, i, j;
	printf("Inputs: ");
	scanf("%d", &n);
	int diff[n][n];
	int equ[n];
	printf("x  y\n");
	for (i = 0; i < n; i++) {	
		printf("%d  ", i);
		scanf("%d", &diff[0][i]);
	}
	for (i = 1; i < n; i++) {	
		for (j = 0; j < n-i; j++) diff[i][j] = diff[i-1][j+1] - diff[i-1][j];
	}
	for (i = 0; i < n; i++) {
		int sub = 0;
		for (j = 0; j < i; j++) sub += coef(n-i, n-j-1) * equ[j];
		equ[i] = (diff[n-i-1][1] - sub) / coef(n-i, n-i-1);
	}
	format(equ, n);
	return 0;
}

int pascal(int pos, int rows) {
	int a = 1, i;
	for(i = 0; i <= rows-1; i++) {
		a = (i == 0) ? 1 : a * (rows-i) / i;
		if (pos == i) return a;
	}
    	return a;
}

int coef(int pos, int power) {
	int i;
	int sum = 0; 
	int mult = 1;
	for (i = pos; i > 0; i--) {		
		sum += mult * pascal(pos - i, pos) * pow(i, power);
		mult *= -1;
	}
	return sum;
}

void format(int* equ, int len) {
	int i;
	for (i = 0; i < len; i++) {
		int p = len-i-1;
		int power = (p < 2) ? p : 2;
		int coef = (*(equ+i) < 2) ? *(equ+i) : 2;
		if (coef != 0) {
			if (power == 0) printf("%d", *(equ+i));
			else if (power == 1) {
				if (coef == 1) printf("x");
				else printf("%dx", *(equ+i));
			} else {
				if (coef == 1) printf("x^%d", p);
				else printf("%dx^%d", *(equ+i), p);
			}
		}
		if (i != len-1) printf(" + ");
   	}
}
