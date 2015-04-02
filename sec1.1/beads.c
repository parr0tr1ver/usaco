/*
ID: freeord1
LANG: C
TASK: beads
 */

#include <stdio.h>

#define MOST 350

int main()
{
	FILE *fin, *fout;
	char *pcur;
	int len, max = 0;
	char beads[MOST];

	fin = fopen("beads.in", "r");
	if (NULL == fin) {
		perror("open file beads.in failed");
	}

	fscanf(fin, "%d", &len);
	fscanf(fin, "%s", beads);
	fclose(fin);

	char *pend = beads + len - 1;

	int m, n;
	char *pi, *pj;
	pcur = beads;
	while (pcur <= pend) {
		m = n = 0;
		pi = pcur;

		// forward
		char ch = *pcur;
		while (pi <= pend) {
			if (ch == *pi || 'w' == *pi) {
				++m;
				++pi;
			} else {
				break;
			}
		}

		// if pi <= pend, finished forward
		if (pi > pend)
			pi = beads;

		while (pi < pcur) {
			if (ch == *pi || 'w' == *pi) {
				++m;
				++pi;
			} else {
				break;
			}
		}

		// all same color
		if (pi == pcur) {
			max = len;
			break;
		}

		// backward
		if (pcur == beads)
			pj = pend;
		else
			pj = pcur - 1;

		if (ch == *pj) {
			++pcur;
			continue;
		}

		// Note: N > 3; pj never meet pi
		while ('w' == *pj) {
			++n;
			if (pj > beads)
				--pj;
			else
				pj = pend;
		}
		ch = *pj;

		// pj never meet pi
		while (pj != pi) {
			if (ch == *pj || 'w' == *pj) {
				++n;
				if (pj > beads)
					--pj;
				else
					pj = pend;
			} else {
				break;
			}
		}

		if (ch == *pj)
			++n;

		if (max < m + n) {
			max = m + n;
		}

		++pcur;
	}
			
/*
		while (pi < pend) {
			if (ch == *pi || 'w' == *pi) {
				++m;
				++pi;
			} else {
				break;
			}
		}

		if (pi == pend) {
			if (ch == *pi || 'w' == *pi) {
				++m;
				pi = beads;
			}
		}

		while (pi != pcur && (ch == *pi || 'w' == *pi)) {
			++pi;
			++m;
		}

		if (pi == pcur) {
			max = m;
			break;
		}

		// deal backward
		ch = *pj;
		while (pj > beads && pj != pi) {
			if (*pj == ch || 'w' == *pj) {
				--pj;
				++n;
			} else {
				break;
			}
		}

		if (pj == pi) {
			if (max < m + n) {
				max = m + n;
				break;
			}
		} else if ((pj == beads) && (*pj == ch || 'w' == *pj)) {
				++n;
				pj = pend;
		} 

		while (pj != pi && (*pj == ch || 'w' == *pj)) {
			--pj;
			++n;
		}

		if (max < m + n) {
#ifdef DEBUG
			printf("%ld: m is %d, n is %d\n", pcur - beads, m, n);
#endif
			max = m + n;
		}

		++pcur;
	} 
*/

	printf("max is %d\n", max);
	fout = fopen("beads.out", "w");
	fprintf(fout, "%d\n", max);

	return 0;
}
