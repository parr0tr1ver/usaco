/*
ID: freeord1
LANG: C
TASK: friday
 */

#include <stdio.h>
#include <string.h>

#define Sun	0
#define Mon	1
#define Tue	2
#define Wed	3
#define Thu	4
#define Fri	5
#define Sat	6

int month[] = {
	0, 31, 28, 31, 30, 31,
	30, 31, 31, 30, 31,
	30, 31
};

int is_leap(int year) {
	if ( (year % 400 == 0) || (year % 100 != 0 && year % 4 == 0))
		return 1;
	else
		return 0;
}

int get_first(int year) {
	int i;
	int sum = 0;

	for (i = 1900; i < year; ++i) {
		if (is_leap(i))
			sum += 366;
		else
			sum += 365;
	}

	return (sum + Mon) % 7;
}


int main()
{
	FILE *fin = fopen("friday.in", "r");
	FILE *fout = fopen("friday.out", "w");

	int result[7];
	int sum, day;
	int N, i, j, k;

	fscanf(fin, "%d", &N);
	fclose(fin);

	memset(result, 0, sizeof(result));

	int year;
	for (year = 1900;  year < 1900 + N; ++year) {
		int first = get_first(year);
		for (j = 1; j < 13; ++j) {
			sum = 0;
			for ( k = 0; k < j; ++k) {
				if (k == 2 && is_leap(year))
					sum += 29;
				else
					sum += month[k];
			}

			day = (sum + 12 + first) % 7;
			result[day]++;
		}
	}

	for (i = 6; i < 12; ++i)
		fprintf(fout, "%d ", result[i % 7]);
	fprintf(fout, "%d\n", result[5]);

	fclose(fout);
	return 0;
}
