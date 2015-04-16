/*
ID: freeord1
LANG: C
TASK: palsquare
 */

#include <stdio.h>

/* 0 -- NEG
 * 1 -- POSITIVE
 */
int is_palindrome(char li[])
{
	char *left, *right;
	left = right = li;
	//while(*right) ++right;
	while(*right++) ;
	right -= 2;

	while (left < right) {
		if (*left == *right) {
			++left;
			--right;
		} else {
			return 0;
		}
	}

	return 1;
}

void reverse(char li[])
{
	char *left, *right;
	left = right = li;
	while (*right++) ;
	right -= 2;

	while (left < right) {
		char t = *left;
		*left = *right;
		*right = t;

		++left;
		--right;
	}
}

void convert(int num, char li[], int base)
{
	int index = 0;
	int mod;

	while (num / base > 0) {
		mod = num % base;
		num /= base;
		li[index++] = mod < 10 ? '0' + mod : 'A' + mod - 10;
	} 

	mod = num % base;
	li[index++] = mod < 10 ? '0' + mod : 'A' + mod - 10;
	li[index] = '\0';

	reverse(li);
}

int main()
{
	FILE *fin, *fout;
	int base, mod;
	
	fin = fopen("palsquare.in", "r");
	if (!fin) {
		perror("open file palsquare.in failed");
		return -1;
	}
	fscanf(fin, "%d", &base);
	fclose(fin);
	
	fout = fopen("palsquare.out", "w");

	char orig[15];
	char list[15];
	int i, j;
	for (i = 1; i <= 300; ++i) {
		convert(i * i, list, base);

		if (is_palindrome(list)) {
			convert(i, orig, base);
			fprintf(fin, "%s %s\n", orig, list);
		}
	}

	fclose(fin);

	return 0;
}
