#include "shdstd.h"

int64_t mod = 1e9 + 7;

int numberOfSets(int n, int k)
{
	int *dp = calloc((k+1), sizeof(int));
	int *prefix = calloc((k+1), sizeof(int));

	dp[0] = 1;

	for (int r = 0; r < n; ++r) {
		for (int i = 0; i < k; ++i) {
			dp[i+1] = (dp[i+1] + prefix[i]) % mod;
		}
		for (int i = 0; i < k; ++i) {
			prefix[i] = (prefix[i] + dp[i]) % mod;
		}
	}

	int res = dp[k];

	free(dp);
	free(prefix);

	return (res + mod) % mod;
}

/* version 0, fully extend

	dp[0][0] = 1;
	for (int r = 1; r < n; ++r) {
		for (int i = 0; i <= k; ++i) {
			dp[r][i] = dp[r-1][i];
		}
		for (int l = 0; l < r; ++l) {
			for (int i = 0; i < k; ++i) {
				dp[r][i+1] += dp[l][i];
			}
		}
	}
	int res = dp[n-1][k];
 */
