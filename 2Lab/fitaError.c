#include <stdio.h>
#include <math.h>

#define PI 3.141592
/*
 cos x = 1 - x^2 / 2! + x^4 / 4! - ...

 |s_k(x) - cos x| \le |a_{k + 1} (x)|

 s_k (x) = a_0(x) + ... + a_k(x)
 a_0(x) = 1
 a_k(x) = (-1)^k \frac{ x^{2k} }{ (2k)! } = - \frac{ x^2 }{ (2k - 1)2k }a_{k-1}(x)

 Fer una taula amb
	- 10000 valors equidistribuits
	- I = [0, 10\pi]
	- 3 columnes
		* x
		* valor calculat cos x
		* error relatiu

L'error, es mes petita que el seguent element que et deixes (pq diu que es alternada)
*/

/*
x \in [0, 10\pi ]
ix increment de x, \pi /1000;

ak resultat trobat

hx for, 10000

k per saber per on vaig

ep epsilon, per saber quan parrar
*/
int main (void)
{
	double x, ix,  ep, x2, sol;
	int hx, k;
	float ak, sk;

	ep = 1e-6;

	ix = PI / 1000.; /* \frac{ 10 \pi - 0 }{ 10000 } */
	x = 0;

	for (hx = 0; hx < 10000; hx++)
	{
		x += ix;
		x2 = x*x;

		ak = 1;
		sk = 0;

		k = 1;

		while ( fabs (ak) >= fabs (sk) * ep)
		{
			sk += ak;
			ak = -ak * x2 / ( k * (k+1) );

			k += 2;
		}

		sol = cos (x);

		printf ("%+e \t %+e %+e\n", x, sk, (sk - sol)/sol );
	}
return 0;
}
