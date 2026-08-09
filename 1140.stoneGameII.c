#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define EXP_MAX (int)(1e2 + 8)
int dp[EXP_MAX][EXP_MAX];
int *arr;
int suffix[EXP_MAX];
int len;

int dfs(int id, int m)
{
	if (id >= len)
		return 0;

	if (dp[id][m] >= 0) {
		return dp[id][m];
	}

	int best = 0;
	for (int i = 0; i < 2 * m && id + i < len; ++i) {
		int nm = MAX(i+1, m);
		int score = suffix[id] - dfs(id+i+1, nm);

		best = MAX(best, score);
	}

	return dp[id][m] = best;
}

int stoneGameII(int *piles, int size)
{
	memset(dp, 0xff, sizeof(dp));
	suffix[size] = 0;
	for (int i = size-1; i >= 0; --i) {
		suffix[i] = suffix[i+1] + piles[i];
	}

	arr = piles;
	len = size;

	return dfs(0, 1);
}
