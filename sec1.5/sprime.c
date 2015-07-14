/*
ID: freeord1
LANG: C
TASK: sprime
 */

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>

// 1 --> true
int isprime(int num)
{
	if (num == 1)
		return 0;

	int i = 2;
	for ( ; i <= sqrt(num); ++i)
		if (num % i == 0)
			return 0;

	return 1;
}

// index is the next empty in primes
int findprime(int bits, int prefix, int primes[], int index)
{
	if (bits == 0)
		return index;

	int i = 1;
	while (i <= 9) {
		if (isprime( 10 * prefix + i)) {
#ifdef Debug
			printf("%d is prime.\n", 10 * prefix + i);
#endif
			if (bits == 1)
				primes[index++] = 10 * prefix + i;
			index = findprime(bits - 1, 10 * prefix + i, primes, index);
		}

		i += prefix == 0 ? 1 : 2;
	}

	return index;
}

int main()
{
	int i;
	int bits;
	int primes[1000];
	FILE *fin, *fout;

	fin = fopen("sprime.in", "r");
	fout = fopen("sprime.out", "w");
	assert(fin && fout);

	fscanf(fin, "%d", &bits);
	memset(primes, 0, 1000 * sizeof(int));

	int index = findprime(bits, 0, primes, 0);

#ifdef Debug
	printf("Index is %d\n", index);
#endif

	for (i = 0; i < index; ++i) {
#ifdef Debug
		printf("%d\n", primes[i]);
#endif
		fprintf(fout, "%d\n", primes[i]);
	}

	fclose(fin);
	fclose(fout);
	return 0;
}
