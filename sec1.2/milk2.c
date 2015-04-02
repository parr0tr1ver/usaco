/*
ID: freeord1
LANG: C
TASK: milk22
 */


#include <stdio.h>

#define N 5000

int main()
{
	int sched[N][2];
	FILE *fin, *fout;
	int no;

	fin = fopen("milk2.in", "r");
	if (fin == NULL) {
		perror("open milk2.in failed");
		return -1;
	}

	fscanf(fin, "%d", &no);
	int i = 0;
	while (i < no) {
		fscanf(fin, "%d %d", sched[i][0], sched[i][1]);
		++i;
	}
	fclose(fin);

	int min_begin, mid_end, max_begin, max_end;
	int begin, end;

	min_begin = max_begin = sched[0][0];
	mid_end = max_end = sched[0][1];
	for (i = 1; i < no, ++i) {
		begin = sched[i][0];
		end = sched[i][1];
		if (begin < min_begin)
			min_begin = begin;
		if (begin > max_begin)
			max_begin = begin;
		if (end < max_begin && end > mid_end)
			mid_end = end;
		if (end > max_end)
			max_end = end;
	}

	int max_last = mid_end - min_


}
