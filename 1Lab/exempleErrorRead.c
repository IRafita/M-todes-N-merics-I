#include <stdio.h>

int main (void)
{
	float x;
	double y;

	printf ("\n Escriu dos digits iguals\n");
	scanf ("%lf", &y);
	scanf ("%f", &x);

	printf ("%.30f\n%.30lf\n", x, y);
return 0;
}
/* Practica 2 */
