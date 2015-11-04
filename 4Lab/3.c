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

void SV (int n, double *v)
{
	int i;
	for (i = 0; i < n; i++)
		printf ("%11.3e", v[i]);
	printf ("\n");
}

double * GV (int n)
{
	double *v;
	v = (double *) malloc (n * sizeof (double));
	if (!v)
	{
		printf ("Error en GV, no vector\n");
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

double * MultUx (int n, double **a, double *x)
{
	int i, j;
	double *b;
	b = GV (n);

	for (i = 0; i < n; i++)
	{
		b[i] = 0;
		for (j = i; j < n; j++)
			b[i] += a[i][j] * x[j];
	}
return b;
}

double * MultLy (int n, double **a, double *x)
{
	int i, j;
	double *b;
	b = GV (n);

	for (i = 0; i < n; i++)
	{
		b[i] = x[i];
		for (j = 0; j < i; j++)
			b[i] += a[i][j] * x[j];
	}
return b;
}

/************* MAIN *****************/
void pra2Ux (int n, double **a, double *b)
{
	a[0][0] = 7; a[0][1] = 5; a[0][2] = 4;
	a[1][0] = 9; a[1][1] = 3; a[1][2] = 2;
	a[2][0] = 9; a[2][1] = 9; a[2][2] = 1;

	b[0] = 8; b[1] = 9; b[2] =11;

	SM (n, a);
	printf ("\n");
	SV (n, b);

	SloveUx_y (n, a, b);
	printf ("\nSolucio\n");
	SV (n, b);
}
void pra2Ly (int n, double **a, double *b)
{
	printf ("\nSegon\n\n");

	a[0][0] = 9; a[0][1] = 9; a[0][2] = 9;
	a[1][0] = 2; a[1][1] = 9; a[1][2] = 9;
	a[2][0] = 0; a[2][1] = 4; a[2][2] = 9;

	b[0] = 7; b[1] = 5; b[2] = 2;
	SM (n, a);
	printf ("\n");
	SV (n, b);

	SloveLy_b (n, a, b);
	printf ("\nSolucio\n");
	SV (n, b);
}
int main (void)
{
	int n;
	double **a, *b, *x;
	n = 3;
	a = GMdBQ (n);
	b = GV (n);

	pra2Ux (n, a, b);
	x = MultUx (n, a, b);
	printf ("Fet el mult\n");
	SV (n, x);

free (x); /* ja em inicialitzat, i tornara a ser-ho */
	pra2Ly (n, a, b);
	x = MultLy (n, a, b);
	printf ("Fet el mult\n");
	SV (n, x);

Mfree (n, a);
free (b);
free (x);
return 0;
}

