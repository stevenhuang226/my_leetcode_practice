#include "shdstd.h"

#define MOD 1000000007

int xorAfterQueries(int *nums, int nums_size,
	int **queries, int queries_size, int *queries_col_size)
{
	for (int i = 0; i < queries_size; ++i) {
		int left = queries[i][0];
		int right = queries[i][1];

		int step = queries[i][2];

		int64_t mult = queries[i][3];

		for (int i2 = left; i2 <= right; i2 += step) {
			nums[i2] =
			(int32_t)(((int64_t)nums[i2] * mult) % MOD);
		}
	}

	int res = 0;
	for (int i = 0; i < nums_size; ++i) {
		res ^= nums[i];
	}

	return res;
}
