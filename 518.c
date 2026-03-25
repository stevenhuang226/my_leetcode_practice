#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int change(int amount, int *coins, int coinsSize)
{
	uint32_t *dp = calloc((amount+1), sizeof(uint32_t));
	dp[0] = 1;
	int i,c;
	for (c = 0; c < coinsSize; ++c) {
		int coin = coins[c];
		for (i = coin; i <= amount; ++i) {
			dp[i] += dp[i - coin];
		}
	}


	int res = dp[amount];
	free(dp);

	return res;
}
