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

/* copiat, no se si funciona, almenys no esta comprovat per mi 'Sistach' */
double** producteMatriu ( n, a, b )
	int n; /* dimencio */
	double **a, **b; /* matrius d'entrada */
{
	double **c; /* el valor que tornarem */
	int i, j, k;

	c = GMdBQ ( n );

	for ( i = 0; i < n; i++ )
		for ( j = 0; j < n; j++ )
		{
			c[i][j] = 0;
			for ( k = 0; k < n; k++ )
				c[i][j] += a[i][k] * b[k][j];
		}
return c;
}

/*
\|A\|_\inf_{0 <= i <= n-1\\ 0 <= j <= n-1} = max_{0<=i<=n-1} (sum_{j=0} |a_ij|)
*/
double norma (int n, **a)
{
	double norm;	/* norma trobada */
	double s;	/* valor temporal, possible norma */
	int i, j;

	norm = 0;
	for (i = 0; i < n; i++)
	{
		s = 0;
		for (j = 0; j < n; j++)
			s += fabs (a[i][j]);
		if (s > norm) norm = s;
	}
return norm;
}

/*
PA = LU,
retorna P, LU
*/
double lupp (int n, double **A, int *p)
{
/* DBL_EPSILON presicio del pc */
	double *vaux	/* vector auxiliar */
	double m;	/* multiple Gauuss */
	double det;	/* l'enunciat el demana */
	double tpM;	/* usat per buscar el maxim */
	double tol;	/* Tolerancia que farem anar */
	int iM;		/* index del maxim buscat */
	int i, j, k;

/************ INICIALITZACIO ****************/
/* inicialitzem el determinant */
	det = 1;

/* inicialitzem p */
	for (i = 0; i < n; i++)
		p[i] = i;

/* calculem la tolerancia */
	tol = DBL_EPSILON * norma (n, A);


/****** Eliminacio gaussiana amb permutacions ********/
	for (k = 0; k < n -1; k++)
	{
/* Cerquem l'element mes gran */
		iM = 0;
		m = fabs(a[k][k]);
		for (i = k+1; i < n; i++) /* +1, ja que no volem tornar a buscar el mes gran */
		{
			tpM = fabs (a[i][k]);
			if (m < tpM)
			{
				iM = i;
				m = tpM;
			}
		}
/* Ens assegurem que el resultat esta dins de la tolerancia */
		if (tol > fabs (m)) { printf ("tolerancia\n"); exit (1); }
		if (iM)/* efectuem un canvi  'Permutacio' */
		{
			det *= -1;

			/* matriu i vector de permutacio */
			vaux = a[iM];	i = p[iM];
			a[iM] = a[k];	p[iM] = p[k];
			a[k] = vaux;	p[k] = i;
		}
		tpM = a[k][k];
		det *= tpM;

/* Ara tocaria la eliminacio gaussiana */
		for (i = k+1; k < n; k++)
		{
			m = a[i][k]/tpM;
			a[i][k] = m;
			for (j = k+1; j < n; j++)
				a[i][j] -= m * a[k][j];
		}
	}
return det; /* es el que demana l'enunciat */
}

/* p(z) = b[0] + b[1] (z - x[0]) + b[2] (z - x[0])(z - x[1])... */
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
		out = out ( z - x[i] ) + b[i];
return out;
}

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
