#include <stdlib.h>
#include <stdio.h>

void SM (int n, double **a)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			printf ("%11.3e", a[i][j]);
		printf ("\n");
	}
}

/*
 * Genera una matriu de double buida quadrada
 */
double ** GMdBQ (int n)
{
	double **a;
	a = (double **) malloc (n * sizeof (double *));
	if (!a)
	{
		printf ("Error en GMBQ, no vector punter\n");
		exit (1);
	}

	while (n--)
	{
		a[n] = (double *) malloc (n * sizeof (double));
		if (!a[n])
		{
			printf ("Error en GMBQ, no vector de doubles\n");
			exit (1);
		}
	}
	return a;
}

void Mfree (int n, double **a)
{
	while (n--)
		free (a[n]);
	free (a);
}

int main (void)
{
	int n;
	double **a;

/* Init */
	n = 3;
	a = GMdBQ (n);
	b = GMdBQ (n);

Mfree (n, a);
Mfree (n, b);
return 0;
}
