/* http://helloitworks.com/678.html */

#include <stdio.h>
#include <stdlib.h>

#define N 8

int a[N] = {0};

int solution = 0;

int isOK(int row, int col)
{
	int i = 0;
	for ( ; i < row; ++i) {
		if (a[i] == col || abs(a[i] - col) == row - i)
			return 0;
	}

	return 1;
}

void display()
{
	printf("Solution No. %d: \n", ++solution);

	int i, j;
	for (i = 0; i < N; ++i) {
		for (j = 0; j < N; ++j) {
			if (a[i] == j)
				printf("%d", i);
			else
				printf("#");
		}
		printf("\n");
	}

	printf("--------------------------\n");
}

void DSF(int row)
{
	int col;
	for (col = 0; col < N; col++)
	{
		if (isOK(row, col)) {
			a[row] = col;
			if (row != N - 1)
				DSF(row + 1);
			else
				display();
		}
	}
}

int main()
{
	DSF(0);

	return 0;
}
