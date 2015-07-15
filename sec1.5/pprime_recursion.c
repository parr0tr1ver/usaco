/*
ID: freeord1
LANG: C
TASK: pprime
 */

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <assert.h>

int min, max;

int is_prime(int num)
{
	int i;
	for (i = 2; i <= sqrt(num); ++i)
		if (num % i == 0)
			return 0;

	return 1;
}

int get_n_bits_pprime(int nbits, int factors[], int f_index, int result[], int index) 
{
	if ( (nbits % 2 == 0 && f_index >= nbits /2 ) || (nbits % 2 == 1 && f_index > nbits / 2)) {
		int foo = 0;
		int i = 0;
		for ( ; i < nbits; ++i) 
			foo = 10 * foo + factors[i];

		if (foo >= min && foo <= max && is_prime(foo))
			result[index++] = foo;

		return index;
	}

	int j = f_index == 0 ? 1 : 0;
	for ( ; j <= 9; ++j) {
		factors[f_index] = j;
		factors[nbits - 1 - f_index] = j;
		index = get_n_bits_pprime(nbits, factors, f_index + 1, result, index);
	}

	return index;
}


void calc_pprime(int result[])
{
	int minbits, maxbits;
	int foo, bar;
	int index = 0;
	int factors[10];

	memset(factors, 0, sizeof(factors));

	minbits = maxbits = 1;
	foo = min;
	while (foo / 10) {
		foo /= 10;
		++minbits;
	}

	foo = max;
	while (foo / 10) {
		foo /= 10;
		++maxbits;
	}

	int i = minbits;
	for ( ; i <= maxbits; ++i)
		index = get_n_bits_pprime(i, factors, 0, result, index);
}

int main()
{
	int result[1000];
	FILE *fin, *fout;
	
	fin = fopen("pprime.in", "r");
	fout = fopen("pprime.out", "w");
	assert(fin && fout);

	fscanf(fin, "%d %d", &min, &max);
	
	memset(result, 0, sizeof(result));

	calc_pprime(result);

	int i = 0;
	while (result[i] != 0)
		fprintf(fout, "%d\n", result[i++]);

	fclose(fin);
	fclose(fout);
	return 0;
}
