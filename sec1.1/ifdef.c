#include <stdio.h>

int main()
{
#ifdef DEBUG
	printf("DEBUG is defined.\n");
#endif
	printf("in main.\n");

	return 0;
}
