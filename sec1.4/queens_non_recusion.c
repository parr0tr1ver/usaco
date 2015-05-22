/* http://helloitworks.com/678.html */

#include <stdio.h>
#include <stdlib.h>

#define N 8

int a[N] = {0};

int solution = 0;

struct Node
{
	int row;
	int col;
};

int isOK(struct Node node)
{
	int i;
	for (i = 0; i < node.row; ++i) {
		if (a[i] == node.col || abs(a[i] - node.col) == node.row - i)
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

// use stack
void DSF()
{
	struct Node stack[10];
	struct Node node;
	node.row = 0;
	node.col = 0;

	int sp = 0;
	stack[sp] = node;
	while (sp >= 0) {
		/* find */
		node = stack[sp];
		while (node.col < N && !isOK(node))
			++node.col;

		if (node.col < N) {
			if (node.row < N - 1) {
				a[node.row] = node.col;
				stack[sp] = node;

				/* next floor */
				++node.row;
				node.col = 0;
				stack[++sp] = node;
			} else {
				/* done */
				a[node.row] = node.col;
				display();

				++node.col;
				stack[sp] = node;
			}
		} else {
			/* back */
			--sp;
			if (sp < 0)
				return ;

			++stack[sp].col;
		}
	}
}

int main()
{
	DSF();

	return 0;
}
