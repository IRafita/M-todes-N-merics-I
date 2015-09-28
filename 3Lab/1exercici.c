#include <stdio.h>
#include <math.h>

void
ShowMan (int n, float x, double e, double nivi)
{	double z = pow (e, n-1);
	printf ("%d\t %e\t %e\t %e\t %e\t %e\n", n, z, nivi, x, x-z, (x-z)/z);	
}

int
main (void)
{
	int n;
	float xn, xv, xt; /* xn es l'ultim valor; xv es el vell */
	double dn, dv, dt; /* xn es l'ultim valor; xv es el vell */
	double z, errorV, errorN;
	z = 1 - sqrt (3);

	xv = 1;
	dv = 1;
	dn = z;
	xn = 1 - sqrtf (3); /* sqrtf pq treballo amb flotants */
	printf ("n\tz\td x \tf x\tx-z\t(x-z)/z error abs/ err abs anterior\n");

	for (n = 3; n < 50; n++)
	{
		xt = 2* (xn + xv);
		xv = xn;
		xn = xt;

		dt = 2* (dn + dv);
		dv = dn;
		dn = dt;

		ShowMan (n, xn, z, dn);
	}

return 0;
}
