#include <float.h>

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
		for (i = k+1; k < n; i++) /* +1, ja que no volem tornar a buscar el mes gran */
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

			/* matriu */
			vaux = a[iM];
			a[iM] = a[k];
			a[k] = vaux;

			/* vector de permutacio */
			i = p[iM];
			p[iM] = p[k];
			p[k] = i;
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
