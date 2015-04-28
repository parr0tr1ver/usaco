/*
ID: freeord1
LANG: C
TASK: skidesign
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <math.h>

int compare(const void *p, const void *q)
{
	return *(const int *)p - *(const int *)q;
}

int main()
{
	int hills, elevation[1000];
	FILE *fin, *fout;

	fin = fopen("skidesign.in", "r");
	fout = fopen("skidesign.out", "w");
	assert(fin && fout);

	fscanf(fin, "%d", &hills);
	int i;
	for (i = 0; i < hills; ++i)
		fscanf(fin, "%d", elevation + i);

	qsort(elevation, hills, sizeof(int), compare);
#ifdef DEBUG
	for (i = 0; i < hills; ++i)
		printf("%d\n", elevation[i]);
#endif

	int cost = INT_MAX;
	int pivot;
	for (pivot = elevation[0]; pivot <= elevation[hills-1]; ++pivot) {
		int add, shorten;
		add = shorten = 0;
		i = 0;
		while (elevation[i] < pivot)
			add += (int)pow(pivot - elevation[i++], 2);

		while (elevation[i] - pivot <= 17) 
			++i;
		
		while (i < hills)
			shorten += (int)pow(elevation[i++] - pivot - 17, 2);

		int sum = add + shorten;
		if (sum < cost) {
#ifdef DEBUG
			printf("pivot is %d, cost will be %d\n", pivot, sum);
#endif
			cost = sum;
		}
	}

	fprintf(fout, "%d\n", cost);

	fclose(fin);
	fclose(fout);
	return 0;
}
