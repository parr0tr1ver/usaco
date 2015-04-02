/*
ID: freeord1
LANG: C
TASK: gift1
 */

/*
 * TODO: how to link the index with the names?
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>

#define NP 10
#define MAXCHAR 14

struct money {
	char name[MAXCHAR];
	int  give;
	int  receive;
};

int main()
{
	int np;
	int initial, fract;
	int i, j, k;
	char id[MAXCHAR];
	struct money *p = NULL;

	FILE *fin = fopen("gift1.in", "r");
	FILE *fout = fopen("gift1.out", "w");

	assert(fin != NULL);
	assert(fout != NULL);

	fscanf(fin, "%d\n", &np);

	struct money all[np];
	memset(all, 0, np * sizeof(struct money));

	for (i = 0; i < np; ++i) {
		fgets(all[i].name, MAXCHAR, fin);
		int len = strlen(all[i].name) - 1;
		all[i].name[len] = '\0';
	}

	for (i = 0; i < np; ++i) {
		fscanf(fin, "%s", id);
		fscanf(fin, "%d %d", &initial, &fract);

		for (j = 0; j < np; ++j) {
			if (!strcmp(id, all[j].name)) {
				p = &all[j];
				break;
			}
		}

		assert(p != NULL);

		if (fract == 0)
			continue;

		p->give = initial - initial % fract;

		for (k = 0; k < fract; ++k) {
			fscanf(fin, "%s", id);
			for (j = 0; j < np; ++j) {
				if (!strcmp(id, all[j].name)) {
					all[j].receive += initial / fract;
					break;
				}
			}
		}
	}

	for (i = 0; i < np; ++i) {
		fprintf(fout, "%s %d\n", all[i].name, all[i].receive - all[i].give);
	}

	fclose(fout);

	return 0;
}
