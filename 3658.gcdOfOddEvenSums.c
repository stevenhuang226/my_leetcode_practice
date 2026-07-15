#include "shdstd.h"

int sgcd(int a, int b)
{
	while (b) {
		int t = a % b;
		a = b;
		b = t;
	}
	return a;
}

int gcdOfOddEvenSums(int n)
{
	int odd_sum = (1 + (n*2-1)) * n / 2;
	int even_sum = (2 + n*2) * n / 2;

	return sgcd(odd_sum, even_sum);
}
