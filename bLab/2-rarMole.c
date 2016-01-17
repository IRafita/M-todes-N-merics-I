#include <math.h>
#include <stdio.h>

int secant ( double *, double, double, double ( double ) );

double fx ( double x ) { return x*x*x - x; } /* -1, 0, 1 son els seus seros */

int main ()
{
	double x[2], iter, prec;
	double a, b, n, h;
	double x0, x1;
	FILE *f1, *f2, *f3;

	remove ( "z.1" );
	remove ( "z.2" );
	remove ( "z.3" );

	f1 = fopen ( "z.1", "w" );
	f2 = fopen ( "z.2", "w" );
	f3 = fopen ( "z.3", "w" );

	iter = 100;
	prec = 1.e-10;

	a = -2;
	b = +2;
	n = 2000;

	h = (b - a)/n;

	for ( x0 = a; x0 <= b; x0 += h )
		for ( x1 = a; x1 <= b; x1 += h )
		{
			x[0] = x0; x[1] = x1;
			if ( 0 == secant (x, prec, iter, fx) )
			{
				n = x[1];
				if ( fabs ( n - 1 ) < .1 )
					fprintf ( f1, "%f %f\n", x0, x1 );
				else if ( fabs ( n ) < .1 )
					fprintf ( f2, "%f %f\n", x0, x1 );
				else
					fprintf ( f3, "%f %f\n", x0, x1 );
			}
		}

fclose ( f1 );
fclose ( f2 );
fclose ( f3 );
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
/*
Plot
plot "z.1" w d, "z.2" w d, "z.3" w d
*/
