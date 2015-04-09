/*
ID: freeord1
LANG: C
TASK: transform
 */

#include <stdio.h>
#include <string.h>

#define NO 10

int rotate_90()
{

	return 1;
}

int rotate_180()
{

	return 2;
}

int rotate_270()
{

	return 3;
}

int reflection()
{

	return 4;
}

int combination()
{
	
	return 5;
}

int compare(char *p1, char *p2, int n)
{
	int i, j;
	for (i = 0; i < n; ++i)
		for (j = 0; j < n; ++i)
			if (p1[i][j] != p2[i][j])
				return 1;

	return 0;
}

int main()
{
	FILE *fin, *fout;
	int result = 0;
	
	fin = fopen("transform.in", "r");
	if (!fin) {
		perror("open file transform.in failed");
		return -1;
	}

	char before[NO][NO];
	char after[NO][NO];
	char tmp[NO][NO];

	printf("sizeof before is %lu\n", sizeof(before));

	memset(before, 0, sizeof(before));
	memset(after, 0, sizeof(after));
	memset(after, 0, sizeof(tmp));

	int n;
	fscanf(fin, "%d", &n);

	int i = 0, j;
	for ( ; i < n; ++i) {
		fscanf(fin, "%s", before[i]);
	}

	for ( i = 0; i < n; ++i) {
		fscanf(fin, "%s", after[i]);
	}

	do {
		if (!compare(before, after, n)) {
			result = 6;
			break;
		}


	} while (0);

	fout = fopen("transform.out", "w");
	fprintf(fout, "%d\n", result);
	fclose(fout);
	fclose(fin);

	return 0;
}
