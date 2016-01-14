#include <stdio.h>
#include <stdlib.h>


double trap ( n, h, integral, a )
	int n; /* intervals dins de [a, b] */
	double h; /* 


/* reciclant */

/* El que he testeixat, m'ha agradat molt la sortida. Crec que funciona adequadament */
/* Hornerd, que tambe dona la derivada */
void hornerd ( n, z, x, f, po )
	int n; /* dimencio */
	double z; /* valor on se vol fer el calcul */
	double *x; /* punts calculats */
	double *f; /* diferencies dividides de newton */
	double po[2]; /* les dues solucions */
{
	int i;

	double p; /* polinomi */
	double d; /* derivada */

	p = f[n -1];
	d = 0;

	for ( i = n -2; i >= 0; i-- )
	{
		d = p + ( z - x[i] ) * d;
		p = p * ( z - x[i] ) + f[i];
	}
po[0] = p;
po[1] = d;
}


/* La funcio sobreescriu els valors de f, escriu alla la solucio */
/* Representa que els punts x son estrictament creixents */
void divdif ( n, x, f )
	int n; /* nombre d'elements de x i f */
	double *x; /* els punts calculats */
	double *f; /* els resultats dels punts */
{
	int i, j;

	for ( i = 1; i < n; i++ )
		for ( j = n -1; j >= i; j-- )
			f[j] = ( f[j] - f[j -1] ) / ( x[j] - x[j - i] );
}

/* Reciclat */

/* p(z) = b[2] + b[1] (z - x[0]) + b[2] (z - x[0])(z - x[1])... */
double horner ( n, b, x, z )
	int n; /* valor d'elements que hi ha en b i x */
	double *b; /* coheficients */
	double *x; /* encara no ho pillo gaire */
	double z;
{
	int i;
	double out;

	out = b[n -1];
	for ( i = n -2; i >= 0; i-- )
		out = out * ( z - x[i] ) + b[i];
return out;
}

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
	double x0, ho[2];
	FILE *F, *G;

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

	F = fopen ( "o.1", "w" );
	G = fopen ( "o.2", "w" );

	h = ( b - a ) / elements;
	for ( x0 = a; x0 <= b; x0 += h )
	{
		hornerd ( n, x0, x, f, ho );
		
		fprintf ( F, "%f %f\n", x0, ho[0] );
		fprintf ( G, "%f %f\n", x0, ho[1] );
	}

free ( x );
free ( f );
return 0;
}
/*
∫²₀ x⁵ dx = x⁶/6]₀² = 2⁶/6 = 32/3 = 10.6666666666666666666666666666666666666666666666666666666


Exerci 1:
	n = 1; h = 2/1 = 2 ⇒ T (h=2) = h/2 [f(0) + f(2)] = 1[0+2⁵] = 32

	n = 2; h = 1  ⇒ T(h=1) = h/2 [f(0) + 2f(1) + f(2)] = ½*32 + h f(1) = 17

	n = 4; h = ½ ⇒ T(h=½) = ½17 + ½[f(½) + f(³/₂)] = 197/16 = 12.3125


∃ funcio double f (_)
main
llegir a, b, prec, num

n = 1, h = (b-a)/n, t₀ = h/2 (f(a) + f(b))
for i = 0; i < num (prec < dif); i++
	n =2n, h = h/2
	t₁ = trap (n, h, t₀, a)
	dif = abs (t₁ - t₀)
	t₀ = t₁

t ← trap (n, h, a, t₀)
*/
