#include "shdstd.h"

#define MOD 1000000007
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int numberOfStableArrays(int zero, int one, int limit)
{
	int64_t dp[zero+1][one+1][2];
	memset(dp, 0,sizeof(dp));

	for (int i = 0; i <= MIN(zero, limit); ++i) {
		dp[i][0][0] = 1;
	}
	for (int i = 0; i <= MIN(one, limit); ++i) {
		dp[0][i][1] = 1;
	}

	for (int z = 1; z <= zero; ++z) {
		for (int o = 1; o <= one; ++o) {
			dp[z][o][0] = dp[z-1][o][0] + dp[z-1][o][1];

			if (z > limit) {
				dp[z][o][0] -= dp[z-limit-1][o][1];
			}
			dp[z][o][0] = (dp[z][o][0] % MOD + MOD) % MOD;

			dp[z][o][1] = dp[z][o-1][0] + dp[z][o-1][1];
			if (o > limit) {
				dp[z][o][1] -= dp[z][o-limit-1][0];
			}
			dp[z][o][1] = (dp[z][o][1] % MOD + MOD) % MOD;
		}
	}

	int res = (dp[zero][one][0] + dp[zero][one][1]) % MOD;

	return res;
}
