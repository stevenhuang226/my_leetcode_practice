#include "shdstd.h"

int sumOfGoodIntegers(int n, int k)
{
	int res = 0;
	for (int x = n+k; x >= n-k; --x) {
		if (x & n)
			continue;
		if (x < 0)
			break;

		res += x;
	}

	return res;
}
