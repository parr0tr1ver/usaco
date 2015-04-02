/*
ID: freeord1
LANG: C
TASK: ride
 */

#include <stdio.h>
#include <assert.h>

int get_mod(char *p)
{
	int mul=1;
	while (*p != '\0')
		mul *= ((*p++) - 'A' + 1);

	return mul % 47;
}

int main()
{
	FILE *fride = fopen("ride.in", "r");
	FILE *fout = fopen("ride.out", "w");
	assert(fride != NULL);
	char comet[9], group[7];
	fscanf(fride, "%s\n", comet);
	fscanf(fride, "%s\n", group);

	int comet_mod = get_mod(comet);
	int group_mod = get_mod(group);

	if (comet_mod == group_mod)
		fprintf(fout, "GO\n");
	else
		fprintf(fout, "STAY\n");


	fclose(fride);
	fclose(fout);
	return 0;
}
