#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define MOD 1000000007

#define INF 1000000000000000
#define NEG_INF -(INF)

int64_t maximumProfit(int *prices, int size, int k)
{
	int64_t dp[k+1][3];

	for (int i = 0; i <= k; ++i) {
		dp[i][0] = 0;
		dp[i][1] = NEG_INF;
		dp[i][2] = NEG_INF;
	}
	/*
	 * 0: do nothing
	 * 1: doing long
	 * 2: doing short
	 */

	for (int day = 0; day < size; ++day) {
		int64_t price = prices[day];

		for (int i = k; i > 0; --i) {
			int64_t prev_non	= dp[i][0];
			int64_t prev_long	= dp[i][1];
			int64_t prev_short	= dp[i][2];

			dp[i][0] = MAX(
				prev_non,
				MAX(dp[i-1][1] + price, dp[i-1][2] - price)
			);

			dp[i][1] = MAX(dp[i][1], prev_non - price);
			dp[i][2] = MAX(dp[i][2], prev_non + price);
		}
		dp[0][1] = MAX(dp[0][1], dp[0][0] - price);
		dp[0][2] = MAX(dp[0][2], dp[0][0] + price);
	}

	return dp[k][0];
}

int main()
{
	int nums[] = {1,7,9,8,2};
	int k = 2;
	int size = sizeof(nums) / sizeof(nums[0]);

	int res = maximumProfit(nums, size, k);
	printf("%d\n", res);

	return 0;
}
