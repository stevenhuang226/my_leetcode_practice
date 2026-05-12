#include "shdstd.h"

int reverse(int x)
{
	int res = 0;
	while (x) {
		res *= 10;
		res += x % 10;
		x /= 10;
	}
	return res;
}

int mirrorDistance(int n)
{
	return abs(n - reverse(n));
}
