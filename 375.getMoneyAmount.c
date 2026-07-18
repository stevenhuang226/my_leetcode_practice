#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MXN (int)2e2 + 8

int dp[MXN][MXN];

int smax(const int left, const int right)
{
	return MAX(left, right);
}

int dfs_best(int left, int right)
{
	if (dp[left][right] >= 0) {
		return dp[left][right];
	}
	int diff = right - left;
	switch (diff) {
		case 0:
			dp[left][right] = 0;
			return 0;
		case 1:
			dp[left][right] = left;
			return left;
	}

	int best = INT32_MAX;
	for (int i = left+1; i < right; ++i) {
		int cost = i + smax(dfs_best(left, i-1), dfs_best(i+1, right));
		best = MIN(best, cost);
	}

	dp[left][right] = best;
	return best;
}

int getMoneyAmount(int n)
{
	memset(dp, 0xff, sizeof(dp));
	return dfs_best(1, n);
}
