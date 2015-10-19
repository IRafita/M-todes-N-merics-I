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

double palu (int n, double **A, int *p)
{
/* DBL_EPSILON presicio del pc */
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
	for (i = 0; i < n; i++)
	{
/* Cerquem l'element mes gran */
		iM = 0;
		tpM = a[i][i];
		for (j = i+1; j < n; j++)
		{
			if (tpM < a[j][i])
			{
				iM = j;
				tpM = a[j][i];
			}
		}
/* Ens assegurem que el resultat esta dins de la tolerancia */
		if (tol > fabs (tpM)){ printf ("tolerancia\n"); exit (1);
		vaux = a[iM];
		a[iM] = a[i];
		a[i] = vaux;
		det *= tpM;
		if (iM)/* em efectuat un canvi */
		{
			det *= -1;
		}

/* Ara tocaria la eliminacio gaussiana */

	}

return det; /* es el que demana l'enunciat */
}
