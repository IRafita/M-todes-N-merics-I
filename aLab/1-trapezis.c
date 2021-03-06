#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

double trapeziBrutus ( n, a, b, f )
	int n; /* intervals dins de [a, b] */
	double a, b; /* valors del interval */
	double f (double); /* la funcio que volem calcular */
{
	double sol;
	double h;
	int i;

	h = (b - a) /n;
	sol = 0;

/* voldria que mostres moltes cossetes ;) */
/* per entendre..
	- f(a) + f(b) /2 *h
	- sumatoria solet
	- sumatori * h
	- resultat
	- resultat sense h
*/
	for ( i = 1; i < n; i++ )
		sol += f ( a + h*i );
/*	printf ( "SUM = %f\t%f\n", sol, sol*h ); */
	sol += ( f ( a ) + f ( b ) ) /2;
/*	printf ( "solucio = %f\t%f\n", sol, sol*h ); */
	sol *= h;
return sol;
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

	double st; /* studi trapezis temporal */

	dif = pre * 2;
	n = 1;
	h = b - a;
	t0 = h * ( f ( a ) + f ( b ) ) / 2;

	for ( i = 0; (i < max) && (pre < dif); i++ )
	{
		n *= 2;
		h /= 2;

		t1 = trap ( n, h, t0, a );
/*
	- No se perque, si poso el comprovant, hi ha casos que peta.
st = trapeziBrutus ( n, a, b, f );
if (st != t1)
	printf ("brutus = %f\npoc a poc = %f\n", st, t1);
*/

		dif = fabs ( t1 - t0 );
		t0 = t1;
	}
return t0;
}

double x2 ( x ) double x; { return x*x*x + 7*x; }
int
main ( void )
{
	double a, b;
	int n;
	double t; /* valor obtingut */
	double pre; /* precisio */

	printf ( " estudi del trapezi brutus\n" );
	a = 0;
	b = 20;
	pre = 1e-10;

	while ( n != -1)
	{
		scanf ("%d", &n);
		t = trapezis ( a, b, n, pre, x2 );
		printf ("%f\n", t);
	}

return 0;
}
