#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

/* Sistema de integracio */
double trap ( n, h, integral, a, f )
	int n; /* intervals dins de [a, b] */
	double h; /* encara no se que representa que es */
	double integral; /* Valor aproximat 2h */
	double a; /* valor on comenzar */
	double f (double); /* la funcio que volem integrar */
{
	int i;

	integral /= 2*h; /* Treiem els valors no necessaris */
	for ( i = 1; i < n; i+= 2 ) /* tots els parells, ja estan del resultat anterior */
		integral += f ( a + h*i );
return integral * h; /* obtenim el resultat final desitjat */
}

/* Sistema per anar directament on se vol */
double trapeziBrutus ( n, a, b, f )
	int n; /* intervals dins de [a, b] */
	double a, b; /* valors del interval */
	double f (double); /* la funcio que volem calcular */
{
	double sum;
	double h;
	int i;

	h = (b - a) /n;
	sum = 0;

	for ( i = 1; i < n; i++ )
		sum += f ( a + h*i );

return h * ( sum + ( f ( a ) + f ( b ) ) /2 );
}

double trapezis ( a, b, max, pre, f )
	double a, b; /* interval */
	int max; /* iteracions maximes */
	double pre; /* precisio desitjada */
	double f (double); /* funcio */
{
	int n; /* subindex */
	int i;
	double h; /* diu l'enunciat, el 'pas' */
	double t0, t1; /* poder calcular presicio */
	double dif; /* calcular precisio */

	/*double st;*/ /* studi trapezis temporal */

	dif = pre * 2;
	n = 1;
	h = b - a;
	t0 = h * ( f ( a ) + f ( b ) ) / 2;

	for ( i = 0; (i < max) && (pre < dif); i++ )
	{
		n *= 2;
		h /= 2;

		t1 = trap ( n, h, t0, a, f );

		dif = fabs ( t1 - t0 );
		t0 = t1;
	}
	printf ( "Trapezis %d\n", i );
return t0;
}

/* Metode de Romberg
extrapolacio repetida de Richardson
formula d'Euler-McLaurin
*/
double extrapolacio ( a, b, max, pre, f )
	double a, b; /* interval */
	int max; /* iteracions maximes */
	double pre; /* precisio desitjada */
	double f (double); /* funcio */
{
	int n; /* subindex */
	double h; /* 'pas' */
	double *t; /* guardar llista */
	double dif; /* calcular presicio */

	int i, j;
	double exT; /* exponent temporal 4^j */

	t = GV ( max );
	dif = pre * 2;
	n = 1;
	h = b - a;
	t[0] = h * ( f ( a ) + f ( b ) ) / 2;

	for ( i = 0; ((i+1) < max) && (pre < dif); i++ )
	{
		n *= 2;
		h /= 2;

		t[i + 1] = trap ( n, h, t[i], a, f );

/* Aixo m'ho he d'estudiar millor */
		exT = 4;
		for ( j = i; j >= 0; j-- )
		{
			t[j] = ( exT * t[j+1] - t[j] ) / ( exT - 1 );
			exT *= 4;
		}

		dif = fabs ( t[1] - t[0] );
	}

	printf ( "extrapolacio %d\n", i );

free ( t );
return t[0];
}

double x2001 ( x ) double x; { return x*x*x + 7*x; }
/* 79 a 2, on el 79 esta igualat a zero */
double x2 ( double x ) { return x*x*x*x - 90 * x * x; }
int
main ( void )
{
	double a, b;
	int n;
	double t; /* valor obtingut */
	double pre; /* precisio */

	printf ( " estudi del trapezi brutus\n" );
	a = 8;
	b = 20;
	pre = 1e-10;
	n=1;

	while ( n != -1)
	{
		t = trapezis ( a, b, n, pre, x2 );
		printf ("%f\n", t);

		t = extrapolacio ( a, b, n, pre, x2 );
		printf ("%f\n", t);

		scanf ("%d", &n);
	}

return 0;
}
