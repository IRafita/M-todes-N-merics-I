#include <stdio.h>

int main ()
{
	int a, i;
	double f;

	a = 1; f = 1;

	for (i = 1; i <= 35; i++)
	{
		a *= i;
		f *= i;
		printf ("%2d\n\t%20d\n\t%20.30lf\n", i, a, f);
	}

return 0;
}


/*
Proposta, fer un programa per a contar rapidament quan arrivara a 2^32
*/
