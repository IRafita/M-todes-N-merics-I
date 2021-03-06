#include <stdlib.h>
#include <stdio.h>

/* Show Matrix */
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

/* Matrix free, allibera la matriu */
void Mfree (int n, double **a)
{
	while (n--)
		free (a[n]);
	free (a);
}


double ** MultipliLU (int n, double **a)
{
	double **b;
	int i, k, j;
	b = GMdBQ (n);

	for (i = 0; i < n; i++)
	{
		for (k = 0; k < i; k++) /* Inicialitzem els zeros */
			b[i][k] = 0;
		for (k = i; k < n; k++) /* Inicialitzem els valors no buits */
			b[i][k] = a[i][k];
	/* Ara comenc,a el programa de debo */
		for (k = 0; k < i; k++)
			for (j = k; j < n; j++)
				b[i][j] += a[i][k] * a[k][j];
	}

return b;
}


int main (void)
{
	int n;
	double **a, **b;

/* Init */
	n = 3;
	a = GMdBQ (n);
/*
1 0 0   7 2 3    7  2  3
3 1 0 x 0 5 4 = 21 11 13
4 1 1   0 0 8   28 13 24
*/
	a[0][0] = 7; a[0][1] = 2; a[0][2] = 3;
	a[1][0] = 3; a[1][1] = 5; a[1][2] = 4;
	a[2][0] = 4; a[2][1] = 1; a[2][2] = 8;

	SM (n, a);

	b = MultipliLU (n, a);

printf ("em acabat\n");
	SM (n, b);

Mfree (n, a);
Mfree (n, b);
return 0;
}
