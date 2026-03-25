#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

inline int min(int a, int b)
{
	if (a < b) {
		return a;
	} else {
		return b;
	}
}

int coinChange(int *coins, int coinsSize, int amount)
{
	int *dp;
	dp = malloc((amount+1) * sizeof(int));
	dp[0] = 0;
	int i,c;
	for (i = 1; i <= amount; ++i) {
		dp[i] = amount + 1;
	}


	for (i = 1; i <= amount; ++i) {
		for (c = 0; c < coinsSize; ++c) {
			int coin = coins[c];
			if (i < coin) continue;
			dp[i] = min(dp[i], dp[i - coin] + 1);
		}
	}

	int res = dp[amount];

	free(dp);

	if (res == amount + 1) {
		return -1;
	} else {
		return res;
	}
}
