#include <stdio.h>
#include <stdlib.h>


/* La funcio sobreescriu els valors de f, escriu alla la solucio */
/* Representa que els punts x son estrictament creixents */
void divdif ( n, x, f )
	int n; /* nombre d'elements de x i f */
	double *x; /* els punts calculats */
	double *f; /* els resultats dels punts */
{
	int k, j;

	for ( k = 1; k < n; k++ )
		for ( j = n -1; j >= k; j-- )
/* important aquest j = n-1, ja que sino entres fora del vector */
			f[j] = ( f[j] - f[j -1] ) / ( x[j] - x[j - k] );
}

/* Reciclat */

/* p(z) = b[0] + b[1] (z - x[0]) + b[2] (z - x[0])(z - x[1])... */
double horner ( n, b, x, z )
	int n; /* valor d'elements que hi ha en b i x */
	double *b; /* coheficients */
	double *x; /* encara no ho pillo gaire */
	double z;
{
	int i;
	double s;

	s = b[n -1];
	for ( i = n -2; i >= 0; i-- )
		s = s * ( z - x[i] ) + b[i];
return out;
}

/* tot 4 */

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
		printf ("%11.3e", v[i]);
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

int main ()
{
/* per la funcio principal */
	int n, i;
	double *x, *f;

/* per printejar */
	double a, b, h, elements;
	double x0;
	FILE *F;

	scanf ( "%d", &n );

	x = GV ( n );
	f = GV ( n );

	for ( i = 0; i < n; i++ )
	{
		scanf ( "%lf", &x[i] );
		scanf ( "%lf", &f[i] );
	}

/* Ja comenzem a fer coses */
	divdif ( n, x, f );

/* Ara faltaria fer el print */
	a = -2;
	b = 6;

	elements = 10000;

	F = fopen ( "out", "w" );

	h = ( b - a ) / elements;
	for ( x0 = a; x0 <= b; x0 += h )
		fprintf ( F, "%f %f\n", x0, horner ( n, f, x, x0 ) );

free ( x );
free ( f );
return 0;
}
