#include <math.h>
#include <stdio.h>

int secant ( double *, double, double, double ( double ) );

void l ()
{
	int i = 5;
	while ( i-- )
		printf ( "%3d\n", i );
	printf ( "Final: %d\n", i );
}

double fx ( double x ) { return x*x*x - x; } /* -1, 0, 1 son els seus seros */

int main ()
{
	double x[2];
x[0] = 1; /* Prec 1.e-10, iter 30 */
x[1] = 2;

printf ( "Sortida: %d\n", secant (x, 1e-10, 30, fx) );

printf ( "Resultat: %f\n", x[1] );

return 0;
}



int secant ( x, prec, iter, fun )
	double *x;
	double prec;
	double iter;
	double fun ( double );
{
	double x0, x1, xt, f0, f1;
	x0 = x[0]; f0 = fun ( x0 );
	x1 = x[1]; f1 = fun ( x1 );
	while ( ( iter-- ) && ( fabs ( x1 - x0 ) >= prec ) && ( fabs ( x1 ) ) )
	{
		xt = x1 - f1 * ( x1 - x0 ) / ( f1  - f0 );
		x0 = x1; f0 = f1;
		x1 = xt; f1 = fun ( x1 );
	}
	x[0] = x0; x[1] = x1;
if ( iter + 1 ) return 0;
return 1;
}
