#include "shdstd.h"

#define MOD 1000000007

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int d_row[] = {0, 1};
int d_col[] = {1, 0};

int maxProductPath(int **grid, int grid_size, int *grid_col_size)
{
	int rows = grid_size;
	int cols = grid_col_size[0];

	int64_t dp[rows][cols][2]; /* dp[r][c][0] => non-negative, [1] => negative */

	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			dp[r][c][0] = -1;
			dp[r][c][1] = 1;
		}
	}

	dp[0][0][0] = grid[0][0];
	dp[0][0][1] = grid[0][0];

	for (int r = 0; r < rows; ++r) {
		for (int c = 0; c < cols; ++c) {
			int64_t curr_max = dp[r][c][0];
			int64_t curr_min = dp[r][c][1];

			for (int i = 0; i < 2; ++i) {
				int new_r = r + d_row[i];
				int new_c = c + d_col[i];

				if (new_r >= rows || new_c >= cols) {
					continue;
				}

				int64_t mult_max = (curr_max * grid[new_r][new_c]);
				int64_t mult_min = (curr_min * grid[new_r][new_c]);

				dp[new_r][new_c][0] =
					MAX(dp[new_r][new_c][0], mult_max);
				dp[new_r][new_c][0] =
					MAX(dp[new_r][new_c][0], mult_min);
				dp[new_r][new_c][1] =
					MIN(dp[new_r][new_c][1], mult_max);
				dp[new_r][new_c][1] =
					MIN(dp[new_r][new_c][1], mult_min);
			}
		}
	}

	int64_t result = dp[rows-1][cols-1][0];

	if (result < 0) {
		return -1;
	}
	return result % MOD;
}
