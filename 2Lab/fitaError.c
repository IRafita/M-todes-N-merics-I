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
*/

int main (void)
{

return 0;
}
