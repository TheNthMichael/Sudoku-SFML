#include "mathtools.h"

/*
General Purpose mapping algorithm
 - Use this to map a value in a given range to another range
	ex: f(x) => g(w) | f(0.5) 0 <= x <= 1	::transformed::		g(5) 0 <= w <= 10
*/
double map(double value, double domain_min, double domain_max, double codomain_min, double codomain_max)
{
	return (value - domain_min) * (codomain_max - codomain_min) / (domain_max - domain_min) + codomain_min;
}

int max(int a, int b) {
	if (a > b)
		return a;
	return b;
}
int min(int a, int b) {
	if (a < b)
		return a;
	return b;
}
