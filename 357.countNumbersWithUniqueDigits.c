#include "shdstd.h"

int countNumbersWithUniqueDigits(int n)
{
	if (n == 0)
		return 1;

	int sum = 10;
	int dp = 9;
	int curr = 10;
	for (int i = 1; i < n; ++i) {
		dp *= (curr-=1);
		sum += dp;
	}

	return sum;
}
