#include <stdio.h>
int
main (void)
{
	int i;
	float	fu = 1;
	double	du = 1;

	i = 0;
	while (1 + fu > 1)
	{ fu /= 2; i++; }
	printf ("float: %d\n", i);

	i = 0;
	while (1 + du > 1)
	{ du /= 2; i++; }
	printf ("float: %d\n", i);
return 0;
}
