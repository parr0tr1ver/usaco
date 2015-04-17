/*
ID: freeord1
LANG: C
TASK: dualpal
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>

int is_palidrome(int num, int base)
{
	char li[1000];
	int mod;
	int i = 0;

	while (num / base > 0) {
		mod = num % base;
		num /= base;
		/* 2 <= base <= 10 */
		li[i++] = '0' + mod;
	}

	li[i] = '0' + num;
	li[i+1] = '\0';


	i = 0;
	int j = strlen(li) - 1;
	while (i < j && li[i] == li[j]) {
		++i;
		--j;
	}

	if (i < j)
		return 0;
	else
		return 1;

}

/* 1 --> positive
 * 0 --> negative
 */
int is_dualpal(int num)
{
	int count = 0;
	int i;
	for (i = 2; i <= 10; ++i) {
		if (is_palidrome(num, i))
			++count;
		if (count == 2)
			return 1;
	}

	return 0;
}

int main()
{
	FILE *fin, *fout;
	
	fin = fopen("dualpal.in", "r");
	fout = fopen("dualpal.out", "w");
	assert (fin && fout);

	int num, start;
	fscanf(fin, "%d %d", &num, &start);
	fclose(fin);

	int count = 0;

	while (count < num) {
		++start;
		if (is_dualpal(start)) {
			++count;
			fprintf(fout, "%d\n", start);
		}
	}

	fclose(fout);

	return 0;
}
