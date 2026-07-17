#include "shdstd.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX_N (int)1e4 + 8

uint32_t dp[MAX_N];
int numSquares(int n)
{
	memset(dp, 0xff, (n+1) * sizeof(uint32_t));

	dp[0] = 0;
	for (int i = 1; i <= n; ++i) {
		for (int i2 = 1; i2 * i2 <= i; ++i2) {
			dp[i] = MIN(dp[i], dp[i - i2*i2] + 1);
		}
	}

	int res = dp[n];

	return res;
}
