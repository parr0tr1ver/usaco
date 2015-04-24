/*
ID: freeord1
LANG: C
TASK: crypt1
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>

int num_length(int num) 
{
	int len = 0;
	while (num / 10 > 0) ++len;

	return ++len;
}

int compare(int *p, int *q)
{
	return *p - *q;
}

int check_in_array(int *pn, int num)
{
	while (*pn != -1) {
		if (num == *pn)
			return 1;
		++pn;
	}

	return 0;
}

int valid(int num, int *pn, int check)
{
	int len = 0;
	while (num > 0) {
		int mod = num % 10;
		num /= 10;
		++len;
		if (check && len > 3)
			return 0;

		if (!check_in_array(pn, mod))
			return 0;
	}

	return 1;
}

int main()
{
	FILE *fin, *fout;
	int num;
	int array[9];

	fin = fopen("crypt1.in", "r");
	fout = fopen("crypt1.out", "w");
	assert(fin && fout);

	fscanf(fin, "%d", &num);
	memset(array, 0, sizeof(array));
	int i = 0;
	for ( ; i < num; ++i)
		fscanf(fin, "%d", array + i);
	array[i] = -1;

#ifdef DEBUG
	for (i = 0; i < num; ++i)
		printf("%d ", array[i]);

	printf("\n");
#endif

	qsort(array, num, sizeof(int), compare);

	int count = 0;
	int j, k;
	for (i = 0; i < num; ++i)
		for (j = 0; j < num; ++j)
			for (k = 0; k < num; ++k) {
				int faciend = 100 * array[i] + 10 * array[j] + array[k];
				int m, n;
				for (m = 0; m < num; ++m) {
					int f1 = array[m];
					int prod1 = faciend * f1;
					if (!valid(prod1, array, 1))
						continue;
					for (n = 0; n < num; ++n) {
						int f2 = array[n];
						int prod2 = faciend * f2;
						if (valid(prod2, array, 1))
							if (valid(10 * prod1 + prod2, array, 0))
							++count;
					}
				}
			}

	fprintf(fout, "%d\n", count);

	fclose(fin);
	fclose(fout);
	return 0;
}
