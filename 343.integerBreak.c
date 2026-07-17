#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MXN 60

int smax(const int a, const int b)
{
	return MAX(a, b);
}
int smax4(const int a, const int b, const int c, const int d)
{
	return smax(smax(a, b), smax(c, d));
}

int curr_build = 0;
int dp[MXN];

void init()
{
	dp[0] = 0;
	dp[1] = 1;
	dp[2] = 1;
	curr_build = 2;
}

void build_next()
{
	if (curr_build < 2) {
		init();
	}

	int trg = curr_build + 1;
	int max = 0;

	for (int i = 0; i < trg; ++i) {
		int L = i + 1;
		int R = trg - L;
		int mult = smax4(L * R, dp[L] * R, L * dp[R], dp[L] * dp[R]);
		max = MAX(max, mult);
	}

	dp[trg] = max;
	curr_build = trg;
}

int integerBreak(int n)
{
	while (curr_build < n) {
		build_next();
	}
	return dp[n];
}
