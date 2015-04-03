/*
ID: freeord1
LANG: C
TASK: milk2
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct period {
	struct period *next;
	int begin;
	int end;
};

#define N 5000

/* make a new period */
struct period *new_period(void) {
	return	(struct period *)malloc(sizeof(struct period));
}

int main()
{
	int sched[N][2];
	FILE *fin, *fout;
	int no;

	fin = fopen("milk2.in", "r");
	if (fin == NULL) {
		perror("open milk2.in failed");
		return -1;
	}

	fscanf(fin, "%d", &no);
	int i;
	for (i = 0; i < no; ++i)
		fscanf(fin, "%d %d", &sched[i][0], &sched[i][1]);
	fclose(fin);

	struct period *phead, *ppre;
	struct period *pp = new_period();
	pp->next = NULL;
	pp->begin = sched[0][0];
	pp->end = sched[0][1];

	phead = new_period();
	phead->next = pp;
	phead->begin = 0;
	phead->end = 0;

	int j, count = 0;
	int pre_begin, pre_end;
	int begin, end;
	struct period *pt, *pt2;

	for (i = 1; i < no - 1; ++i) {
		begin = sched[i][0];
		end = sched[i][1];

		/* insert new period to link list */
		ppre = phead;
		pp = phead->next;
		while (pp) {
			if (begin < pp->begin) {
				if (end < pp->begin) {
					pt = new_period();
					pt->next = pp;
					pt->begin = begin;
					pt->end = end;

					ppre->next = pt;
					break;
				} else if (end >= pp->begin && end <= pp->end) {
					pp->begin = begin;
					break;
				} else if (end > pp->end) {
					pp->end = end;
					pt = pp->next;
					while (pt) {
						if (end < pt->begin) {
							break;
						} else if(end >= pt->begin && end <= pt->end) {
							pp->next = pt->next;
							pp->end = pt->end;
							free(pt);
							break;
						} else {
							pt2 = pt;
							pt = pt->next;
							free(pt2);
						}
					}
				}
			} else if (begin >= pp->begin && begin <= pp->end) {
				if (end <= pp->end) {
					break;
				} else {
					pp->end = end;
					pt = pp->next;
					while (pt) {
						if (end < pt->begin) {
							break;
						} else if (end >= pt->begin && end <= pt->end) {
							pp->next = pt->next;
							pp->end = pt->end;
							free(pt);
							break;
						} else {
							pt2 = pt;
							pt = pt->next;
							free(pt2);
						}
					}
				}
			} else { /* begin > pp->end */
				ppre = pp;
				pp = pp->next;

				if (!pp || end < pp->begin) {
					pt = new_period();
					pt->begin = begin;
					pt->end = end;

					ppre->next = pt;
					pt->next = pp;

					break;
				}
			}
		}
	}

	int max_active = 0, max_idle = 0;
	ppre = phead;
	for (pp = phead->next; pp != NULL; pp = pp->next) {
		if (ppre != phead && max_idle < pp->begin - ppre->end)
			max_idle = pp->begin - ppre->end;

		if (max_active < pp->end - pp->begin)
			max_active = pp->end - pp->begin;

		ppre = pp;
	}

//	printf("max_active is %d, max_idle: %d\n", max_active, max_idle);
	fout = fopen("milk2.out", "w");
	fprintf(fout, "%d %d\n", max_active, max_idle);
	fclose(fout);

	pp = phead;
	while (pp) {
		ppre = pp;
		pp = pp->next;
		free(ppre);
	}

	return 0;
}
