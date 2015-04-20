/*
ID: freeord1
LANG: C
TASK: milk
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>

int compare(int *p, int *q)
{
	return *p - *q;
}

int main()
{
	FILE *fin, *fout;
	int pay, amount, farmers;
	int stock[5000][2];

	fin = fopen("milk.in", "r");
	fout = fopen("milk.out", "w");
	assert( fin && fout);

	fscanf(fin, "%d %d", &amount, &farmers);

	int i;
	memset(stock, 0, sizeof(stock));
	for (i = 0; i < farmers; ++i)
		fscanf(fin, "%d %d", &stock[i][0], &stock[i][1]);
	fclose(fin);

	qsort(stock, farmers, 2 * sizeof(int), compare);
#ifdef DEBUG
	for (i = 0; i < farmers; ++i)
		printf("%d %d\n", stock[i][0], stock[i][1]);
#endif

	pay = 0;
	for (i = 0; i < farmers; ++i) {
		int price = stock[i][0];
		int num = stock[i][1];

		if (amount > num) {
			pay += price * num;
			amount -= num;
		} else {
			pay += price * amount;
			break;
		}
	}
	
	fprintf(fout, "%d\n", pay);
	fclose(fout);

	return 0;
}
