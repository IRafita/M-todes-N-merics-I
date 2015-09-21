#include <stdio.h>

int main (void)
{
	int i = 10,x = 1;
	while (i--)
	{
		printf ("%4d%20d\n", 10 -i, x);
		x *= 10;
	}
	printf ("%24d\n", x);
return 0;
}
/* Practica 1 */
