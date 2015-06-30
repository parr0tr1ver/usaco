/*
ID: freeord1
LANG: C
TASK: pprime
 */

#include <stdio.h>
#include <math.h>
#include <assert.h>

/* 0 --> negative
 * 1 --> positive
 */
int isprime(int num)
{
	int i = 2;
	for ( ; i <= sqrt(num); ++i) {
		if (num % i == 0)
			return 0;
	}

	return 1;
}

int ispalin(int num)
{
	int i, j;
	int str[10];
	int index = 0;
	while (num > 0) {
		str[index++] = num % 10;
		num /= 10;
	}

#ifdef Debug
	for (i = 0; i < index; ++i) {
		printf("%d, ", str[i]);
	}
	printf("\n");
#endif

	for (i = 0, j = index - 1; i <= j; i++, j--) {
		if (str[i] != str[j])
			return 0;
	}

	return 1;
}

int main()
{
	int floor, top;
	FILE *fin, *fout;
	int i;

	fin = fopen("pprime.in", "r");
	fout = fopen("pprime.out", "w");
	assert(fin && fout);

	fscanf(fin, "%d %d", &floor, &top);

	for (i = floor; i <= top; ++i) {
		if (ispalin(i) && isprime(i)) {
#ifdef Debug
			printf("got one: %d\n", i);
#endif

			fprintf(fout, "%d\n", i);
		}
	}

	fclose(fin);
	fclose(fout);
	return 0;
}
