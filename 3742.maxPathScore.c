#include "shdstd.h"

#define INF32 (INT32_MAX / 4)
#define NEG_INF32 -(INF32)

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

static inline int32_t smaxi32(const int32_t a, const int32_t b)
{
	return MAX(a, b);
}

int maxPathScore(int **grid, int size, int *col_size, int k)
{
	int rows = size;
	int cols = col_size[0];

	int dp[rows+1][cols+1][k+1];
	memset(dp, 0xf0, (rows+1) * (cols+1) * (k+1) * sizeof(int));

	dp[1][1][0] = 0;
	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			if (r == 0 && c == 0) continue;

			int curr = grid[r][c];
			if (curr == 0) {
				for (int i = 0; i <= k; ++i) {
					int top = dp[r][c+1][i];
					int left = dp[r+1][c][i];
					dp[r+1][c+1][i] = smaxi32(left, top);
				}
				continue;
			}
			for (int i = 0; i < k; ++i) {
				int top = dp[r][c+1][i];
				int left = dp[r+1][c][i];
				dp[r+1][c+1][i+1] = smaxi32(left, top) + curr;
			}
		}
	}

	int res = -1;

	for (int i = 0; i <= k; ++i) {
		res = smaxi32(res, dp[rows][cols][i]);
	}

	return res;
}
