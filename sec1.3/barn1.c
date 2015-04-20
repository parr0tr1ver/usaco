/*
ID: freeord1
LANG: C
TASK: barn1
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>

// descend order
int compare(int *p, int *q)
{
	return *p - *q;
}

int cal_intervals(int *stalls, int *intervals, int num)
{
	int segs = 0;
	int inter;
	int i = 0;
	while (i < num && stalls[i] == 0) ++i;
	
	while (i < num) {
		while (i < num && stalls[i] != 0) ++i;
		inter = 0;
		while (i < num && stalls[i] == 0) {
			++i;
			++inter;
		}
		if (i < num) {
			intervals[segs] = inter;
			++segs;
		}
	}

	return segs + 1;
}

int main()
{
	FILE *fin, *fout;
	int num_board, num_stall, num_cow;
	int result;
	int intervals[100];
	int stalls[200];

	fin = fopen("barn1.in", "r");
	fout = fopen("barn1.out", "w");
	assert(fin && fout);
	fscanf(fin, "%d %d %d", &num_board, &num_stall, &num_cow);
	
	memset(stalls, 0, sizeof(stalls));
	int i, index;
	for (i = 0; i < num_cow; ++i) {
		fscanf(fin, "%d", &index);
		stalls[index - 1] = 1;
	}

	memset(intervals, 0, sizeof(intervals));
	int segs = cal_intervals(stalls, intervals, num_stall);
	if (segs <= num_board) {
		result = num_cow;
	} else {
		qsort(intervals, segs - 1, sizeof(int), compare);
		result = 0;
		for (i = 0; i < segs - num_board; ++i)
			result += intervals[i];
		result += num_cow;
	}
	
	fprintf(fout, "%d\n", result);

	fclose(fin);
	fclose(fout);
	return 0;
}
