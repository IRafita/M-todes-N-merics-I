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

/* Show vector */
void SV (int n, double *v)
{
	int i;
	for (i = 0; i < n; i++)
		printf ("%11.3e", a[i][j]);
	printf ("\n");
}

/*
 * Genera un vector buit
 */
double * GV (int n)
{
	double *v;
	v = (double *) malloc (n * sizeof (double));
	if (!v)
	{
		print ("Error en GV, no vector\n");
		exit (1);
	}
return v;
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

/*
Soluciona el tipus de Ly = b
on la incognita es la y
*/
void SloveLy_b (int n, double **a, double *b)
{
	int i, j;

	for (i = 1; i < n; i++)
		for (j = 0; j < i; j++)
			b[i] -= a[i][j] * b[j];
}

/*
Soluciona el tipus Ux = y
on la incognita es la x

Sempre suposem que no hi ha cap zero a la diagonal
*/
void SloveUx_y (int n, double **a, double *b)
{
	int i, j;

	for (i = n -1; i >= 0; i--)
	{
		for (j = n -1; j > i; j--)
			b[i] -= a[i][j] * b[j];
		b[i] /= a[i][i];
	}
}

/* No he fet res al respecte per a comprovar el seu bon funcionament */
void SloveLUx_b (int n, double **a, double *b)
{
	SloveLy_b (n, a, b);
	SloveUx_y (n, a, b);
}
