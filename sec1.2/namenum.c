/*
ID: freeord1
LANG: C
TASK: namenum
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#define MAX 5000

/* 0 --> negative
 * 1 -- positive
 */
int is_valid(char *p, char dict[][13])
{
	int left = 0, right = MAX - 1;
	while (left < right) {
		int mid = (left + right) / 2;
		int ret = strcmp(p, dict[mid]);
		if (ret == 0)
			return 1;
		else if (ret > 0)
			left = mid + 1;
		else
			right = mid - 1;
	}
	
	if (left == right && strcmp(p, dict[left]) == 0)
		return 1;
	return 0;
}

int main()
{
	FILE *fin, *fout, *fdict;
	char dict[5000][13];

	fin = fopen("namenum.in", "r");
	fout = fopen("namenum.out", "w");
	fdict = fopen("dict.txt", "r");
	
	assert(fin && fout && fdict);

	int num;
	char li_num[13];
	fscanf(fin, "%s", li_num);
	fclose(fin);
	
	int count = 0;
	memset(dict, 0, sizeof(dict));
	while ( !feof(fdict)) 
		fscanf(fdict, "%s", dict[count++]);

	int i, j, k;
	char keymap[10][4];
	memset(keymap, 0, sizeof(keymap));
	for (i = 2; i < 7; ++i)
		for (j = 0; j < 3; ++j)
			keymap[i][j] = 'A' + 3 * (i - 2) + j;

	strcpy(keymap[7], "PRS");
	strcpy(keymap[8], "TUV");
	strcpy(keymap[9], "WXY");

	int col = strlen(li_num);
	int row = pow(3, col);
	char results[row][col+1];
	memset(results, 0, sizeof(results));

	for (i = 0; i < col; ++i) {
		int power = pow(3, col - 1 - i);
		for (j = 0; j < row; j += 3 * power) {
			int index = li_num[i] - '0';
			for (k = 0; k < power; ++k)
				results[j + k][i] = keymap[index][0];

			for ( ; k < 2 * power; ++k)
				results[j + k][i] = keymap[index][1];

			for ( ; k < 3 * power; ++k)
				results[j + k][i] = keymap[index][2];
		}
	}

	count = 0;
	for (i = 0; i < row; ++i) {
		if (is_valid(results[i], dict)) {
			++count;
			fprintf(fout, "%s\n", results[i]);
		}
	}

	if (count == 0)
		fprintf(fout, "NONE\n");

	fclose(fout);
	return 0;
}
