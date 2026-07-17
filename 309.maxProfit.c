#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
enum state {
	HOLD, SOLD, REST
};

int maxProfit(int *prices, int size)
{
	int **dp = malloc(3 * sizeof(int *));
	int *dp_flat = malloc(3 * size * sizeof(int));
	dp[0] = dp_flat;
	dp[1] = dp_flat + 1 * size;
	dp[2] = dp_flat + 2 * size;

	dp[HOLD][0] = -prices[0];
	dp[SOLD][0] = 0;
	dp[REST][0] = 0;
	for (int i = 0; i < size - 1; ++i) {
		dp[HOLD][i+1] = MAX(dp[REST][i] - prices[i+1], dp[HOLD][i]);
		dp[SOLD][i+1] = dp[HOLD][i] + prices[i+1];
		dp[REST][i+1] = MAX(dp[SOLD][i], dp[REST][i]);
	}

	int max = MAX(dp[REST][size-1], dp[SOLD][size-1]);

	free(dp_flat);
	free(dp);

	return max;
}
