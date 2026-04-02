#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

int maximumAmount(int **coins, int coin_size, int *coin_col_size)
{
	int rows = coin_size;
	int cols = coin_col_size[0];

	if (rows == 1 && cols == 1) {
		return MAX(0, coins[0][0]);
	}

	int64_t dp[3][rows][cols];
	for (int i = 0; i < 3; ++i) {
		for (int i2 = 0; i2 < rows; ++i2) {
			for (int i3 = 0; i3 < cols; ++i3) {
				dp[i][i2][i3] = INT32_MIN;
			}
		}
	}

	dp[0][0][0] = coins[0][0];
	dp[1][0][0] = MAX(coins[0][0], 0);
	dp[2][0][0] = MAX(coins[0][0], 0);


	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			if (r == 0 && c == 0) continue;
			for (int n = 2; n >= 0; --n) {
				int64_t curr = coins[r][c];

				int64_t top = INT32_MIN;
				int64_t left = INT32_MIN;
				if (r - 1 >= 0) {
					top = dp[n][r-1][c];
				}
				if (c - 1 >= 0) {
					left = dp[n][r][c-1];
				}

				dp[n][r][c] = MAX(top, left) + curr;

				if (n < 2) {
					dp[n+1][r][c] = MAX(dp[n][r][c], dp[n+1][r][c]);
					dp[n+1][r][c] = MAX(top, dp[n+1][r][c]);
					dp[n+1][r][c] = MAX(left, dp[n+1][r][c]);
				}
			}
		}
	}

	int result = dp[2][rows-1][cols-1];

	return result;
}
