#include "shdstd.h"

int numTrees(int n)
{
	if (n == 1) {
		return 1;
	}

	int *dp = malloc((n+1) * sizeof(int));
	dp[0] = 1;
	dp[1] = 1;

	int i, i2;
	for (i = 2; i <= n; ++i) {
		dp[i] = 0;
		for (i2 = 1; i2 <= i; ++i2) {
			int l = i2 - 1;
			int r = i - i2;
			dp[i] += dp[l] * dp[r];
		}
	}

	int res = dp[n];
	free(dp);
	return res;
}

int main()
{
	int n = 3;
	printf("o:%d e:5\n", numTrees(n));

	return 0;
}
