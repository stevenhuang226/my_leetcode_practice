#include "shdstd.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
static inline int64_t smax(int64_t a, int64_t b)
{
	return MAX(a, b);
}
static inline int64_t smax3(int64_t a, int64_t b, int64_t c)
{
	return smax(MAX(a, b), c);
}
static inline int64_t smax4(int64_t a, int64_t b, int64_t c, int64_t d)
{
	return smax(MAX(a, b), MAX(c, d));
}

int64_t maximumScore(int **grid, int size, int *col_size)
{
	int rows = size;
	int cols = col_size[0];

	int64_t prefix[cols][rows+1];
	for (int c = 0; c < cols; ++c) {
		prefix[c][0] = 0;
		for (int r = 0; r < rows; ++r) {
			prefix[c][r+1] = prefix[c][r] + grid[r][c];
		}
	}

	int64_t dp[cols][rows+1][2];
	/* col, height, 0: skip 1: pick */
	memset(dp, 0x00, sizeof(dp));

	for (int c = 1; c < cols; ++c) {
		for (int prev = 0; prev <= rows; ++prev) {
			int64_t prev0 = dp[c-1][prev][0];
			int64_t prev1 = dp[c-1][prev][1];

			for (int curr = 0; curr <= rows; ++curr) {
				int64_t prev_gain = 0;
				int64_t curr_gain = 0;

				if (curr > prev) {
					prev_gain = prefix[c-1][curr] - prefix[c-1][prev];
				} else {
					curr_gain = prefix[c][prev] - prefix[c][curr];
				}

				dp[c][curr][0] = smax3(dp[c][curr][0], prev0 + prev_gain, prev1);

				dp[c][curr][1] = smax(dp[c][curr][1],
					smax(prev0 + prev_gain, prev1) + curr_gain);
			}
		}
	}

	int64_t res = 0;
	for (int h = 0; h <= rows; ++h) {
		res = smax(res, dp[cols-1][h][1]);
	}
	return res;
}
