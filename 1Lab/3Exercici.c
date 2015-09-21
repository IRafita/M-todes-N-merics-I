#include <stdio.h>
int main (void)
{
	float x;
	double xx;
	double h, er;
	int i, n;

	n = 10000;

	h = 7./n;

	for (i = 0; i < n; i++)
	{
		x = 1 + i * h;
		xx= 1 + i * h;

		er = (x - xx) / xx;
		printf ("%+e\t%+e\n", xx, er);
	}
}
