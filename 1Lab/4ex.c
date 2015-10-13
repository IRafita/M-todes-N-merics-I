#include <stdio.h>

#define y 0.57721566490153286
int main (void)
{
	double sc, sd;
	int n, k;

	printf ("Iterat, <, e<, >, e>\n");

	/* definim */
	n = 300;
	sc = 0; sd = 0;

	/* Pes gros */
	for (k = 0; k < n; k++)
	{
		sc += 1./(k+1);
		sd += 1./(n -k);

	printf ("%5d \t%e \t%e \t%e \t%e\n", k+1, sc, sc -y, sd, sd -y);
	}
return 0;
}
