/*
ID: freeord1
LANG: C
TASK: milk2
 */

#include <stdio.h>
#include <string.h>

#define N 5000

struct feed {
	int begin;
	int end;
};

void swap(struct feed **p1, struct feed **p2)
{
	struct feed *p;

	p = *p1;
	*p1 = *p2;
	*p2 = p;
}

int get_mid(int a, int b, int c)
{
	int min, max;
	min = max =a;
	if (max < b) max = b;
	if (max < c) max = c;
	if (min > b) min = b;
	if (min > c) min = c;

	if (min < a && a < max) return 0;
	if (min < b && b < max) return 1;

	return 2;
}

void qsort(struct feed *li[], int left, int right)
{
	if (left >= right)
		return ;

	int pivot;
	int begin = left;
	int last = right;
	struct feed *ppivot;

	int mid = get_mid(li[left]->begin, li[(left + right) / 2]->begin, li[right]->begin);
	if (mid ==  1)
		swap(&li[left], &li[(left + right) / 2]);
	else if (mid == 2)
		swap(&li[left], &li[right]);

	pivot = li[left]->begin;
	ppivot = li[left];

	while (left < right) {
		while (left < right && li[right]->begin >= pivot) --right;
		swap(&li[left], &li[right]);
		while (left < right && li[left]->begin < pivot) ++left;
		swap(&li[left], &li[right]);
	}
	li[left] = ppivot;

	qsort(li, begin, left - 1);
	qsort(li, left + 1, last);
}

int main()
{
	FILE *fin, *fout;

	fin = fopen("milk2.in", "r");
	if (!fin) {
		perror("open file milk2.in error");
		return 1;
	}

	struct feed inters[N];
	struct feed *pf[N];
	int num, i, j;

	fscanf(fin, "%d", &num);

	for (i = 0; i < num; ++i) {
		fscanf(fin, "%d %d", &inters[i].begin, &inters[i].end);
		pf[i] = &inters[i];
	}
	fclose(fin);

	printf("num is %d\n", num);
	qsort(pf, 0, num - 1);
	for (i = 0; i < num; ++i)
		printf("%d %d\n", pf[i]->begin, pf[i]->end);

	int milk = 0, idle = 0;
	
	for (i = 0; i < num; ++i) {
		int end = pf[i]->end;
		j = i;
		while (j < num && end >= pf[j]->begin) {
			if (end < pf[j]->end)
				end = pf[j]->end;
			++j;
		}
		
		if (end < pf[j-1]->end)
			end = pf[j-1]->end;

		int foo = end - pf[i]->begin;
		if (foo > milk)
			milk = foo;

		if (j < num) {
			foo = pf[j]->begin - end;
			if (foo > idle)
				idle = foo;
		}

		i = j - 1; // i will ++ then
	}

	fout = fopen("milk2.out", "w");
	fprintf(fout, "%d %d\n", milk, idle);
	fclose(fout);

	return 0;
}

