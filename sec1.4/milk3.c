/*
ID: freeord1
LANG: C
TASK: milk3
 */

// copy from:
// http://www.programlife.net/usaco-mothers-milk-dfs.html

#include <stdio.h>
#include <string.h>
#include <assert.h>

int state[21][21][21];
int A, B, C;
int left[21];
int pull;

void DFS(int a, int b, int c)
{
	if (state[a][b][c]) return ;
	state[a][b][c] = 1;
	
	// FIXME: why do NOT compare b?
	//if (a == 0 || b == B)
	if (a == 0 )
		left[c] = 1;

	// a -> b
	if (a + b < B)
		DFS(0, a + b, c);
	else
		DFS(a - (B - b), B, c);

	// a -> c
	if (a + c < C)
		DFS(0, b, a + c);
	else
		DFS(a - (C - c), b, C);

	// b -> a
	if (b + a < A)
		DFS(a + b, 0, c);
	else
		DFS(A, b - (A - a), c);

	// b -> c
	if (b + c < C)
		DFS(a, 0, b + c);
	else
		DFS(a, b - (C - c), C);


	// c -> a
	if (c + a < A)
		DFS(a + c, b, 0);
	else
		DFS(A, b, c - (A - a));

	// c -> b
	if (c + b < B)
		DFS(a, b + c, 0);
	else
		DFS(a, B, c - (B - b));

	return ;
}

int main()
{
	FILE *fin, *fout;
	fin = fopen("milk3.in", "r");
	fout = fopen("milk3.out", "w");
	assert(fin && fout);

	fscanf(fin, "%d %d %d", &A, &B, &C);

#ifdef DEBUG
	printf("a = %d; b = %d; c = %d\n", A, B, C);
#endif

	memset(state, 0, sizeof(state));
	memset(left, 0, sizeof(left));

	DFS(0, 0, C);

	int i = 0;
	for ( ; i < 21; ++i)
		if (left[i]) {
			fprintf(fout, "%d ", i);
#ifdef DEBUG
			printf("%d ", i);
#endif
		}
	fseek(fout, -1, SEEK_CUR);
	fprintf(fout, "\n");

#ifdef DEBUG
	printf("\n");
#endif

	fclose(fin);
	fclose(fout);
	return 0;
}
