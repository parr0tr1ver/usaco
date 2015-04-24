/*
ID: freeord1
LANG: C
TASK: combo
 */

#include <stdio.h>
#include <assert.h>

int farmer_combo[3], master_combo[3];
int N;

int valid(int *pn)
{
	int count1, count2;
	count1 = count2 = 0;

	int i;
	for (i = 0; i < 3; ++i) {
		int combo = farmer_combo[i];
		int num = *(pn + i);
		if (combo <= 2) {
			if (num >= combo + N - 2 || num <= combo + 2)
				++count1;
		} else if (combo >= N - 1) {
			if (num >= combo - 2 || num >= 1 && num + N <= combo + 2)
				++count1;
		} else {
			if (num >= combo - 2 && num <= combo + 2)
				++ count1;
		}

		combo = master_combo[i];
		if (combo <= 2) {
			if (num >= combo + N - 2 || num <= combo + 2)
				++count2;
		} else if (combo >= N - 1) {
			if (num >= combo - 2 || num >= 1 && num + N <= combo + 2)
				++count2;
		} else {
			if (num >= combo - 2 && num <= combo + 2)
				++count2;
		}
	}

	if (count1 == 3 || count2 == 3)
		return 1;

	return 0;
}

int main()
{
	FILE *fin, *fout;
	int count = 0;

	fin = fopen("combo.in", "r");
	fout = fopen("combo.out", "w");
	assert(fin && fout);

	fscanf(fin, "%d", &N);
	fscanf(fin, "%d %d %d", farmer_combo, farmer_combo + 1, farmer_combo + 2);
	fscanf(fin, "%d %d %d", master_combo, master_combo + 1, master_combo + 2);

	int i, j, k;
	int array[3];
	for (i = 1; i <= N; ++i) {
		array[0] = i;
		for (j = 1; j <= N; ++j) {
			array[1] = j;
			for (k = 1; k <= N; ++k) {
				array[2] = k;
				if (valid(array)) {
#ifdef DEBUG
					printf("%d %d %d\n", i, j, k);
#endif
					++count;
				}
			}
		}
	}

	fprintf(fout, "%d\n", count);

	fclose(fin);
	fclose(fout);
	return 0;
}
