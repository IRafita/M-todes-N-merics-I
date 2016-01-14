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
