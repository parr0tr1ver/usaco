/*
ID: freeord1
LANG: C
TASK: transform
 */

#include <stdio.h>
#include <string.h>

#define NO 10

void rotate_90(char before[][NO], char trans[][NO], int n)
{
	int i, j;
	for (i = 0; i < n; ++i)
		for (j = 0; j < n; ++j)
			trans[i][j] = before[j][n-1-i];
//			trans[j][n-1-i] = before[i][j];
}

void rotate_180(char before[][NO], char trans[][NO], int n)
{
	char tmp[NO][NO];
	memset(tmp, 0, sizeof(tmp));

	rotate_90(before, tmp, n);
	rotate_90(tmp, trans, n);
}

void rotate_270(char before[][NO], char trans[][NO], int n)
{
	char foo[NO][NO];
	char bar[NO][NO];
	memset(foo, 0, sizeof(foo));
	memset(bar, 0, sizeof(bar));

	rotate_90(before, foo, n);
	rotate_90(foo, bar, n);
	rotate_90(bar, trans, n);
}

void reflection(char before[][NO], char trans[][NO], int n)
{
	int i, j;
	for (i = 0; i < n; ++i)
		for (j = 0; j < n; ++j)
			trans[i][j] = before[i][n-1-j];
}

int combination(char before[][NO], char trans[][NO], char target[][NO], int n)
{
	char tmp[NO][NO];
	memset(tmp, 0, sizeof(tmp));

	reflection(before, trans, n);

	int i;
	for (i = 0; i < 3; ++i) {
		rotate_90(trans, tmp, n);
		/* why missing last parameter n is ok?
		if (!compare(trans, target))
		*/
		if (!compare(tmp, target, n))
			return 0;

		memcpy(trans, tmp, sizeof(tmp));
	}

	return 1;
}

int compare(char p1[][NO], char p2[][NO], int n)
{
	int i, j;
	for (i = 0; i < n; ++i)
		for (j = 0; j < n; ++j)
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
	char target[NO][NO];
	char tmp[NO][NO];

	memset(before, 0, sizeof(before));
	memset(target, 0, sizeof(target));
	memset(target, 0, sizeof(tmp));

	int n;
	fscanf(fin, "%d", &n);

	int i = 0, j;
	for ( ; i < n; ++i) {
		fscanf(fin, "%s", before[i]);
	}

	for ( i = 0; i < n; ++i) {
		fscanf(fin, "%s", target[i]);
	}

	do {
		rotate_90(before, tmp, n);
		if (!compare(tmp, target, n)) {
			result = 1;
			break;
		}

		rotate_180(before, tmp, n);
		if (!compare(tmp, target, n)) {
			result = 2;
			break;
		}

		rotate_270(before, tmp, n);
		if (!compare(tmp, target, n)) {
			result = 3;
			break;
		}

		reflection(before, tmp, n);
		if (!compare(tmp, target, n)) {
			result = 4;
			break;
		}

		if (!combination(before, tmp, target, n)) {
			result = 5;
			break;
		}

		if (!compare(before, target, n)) {
			result = 6;
			break;
		}

		result = 7;
	} while (0);

	fout = fopen("transform.out", "w");
	fprintf(fout, "%d\n", result);
	fclose(fout);
	fclose(fin);

	return 0;
}
