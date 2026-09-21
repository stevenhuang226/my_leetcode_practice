#include "shdstd.h"

int64_t *resultArray(int *nums, int size, int k, int *ret_size)
{
	int64_t *res = calloc(k, sizeof(int64_t));

	int64_t dp[k * 2];

	memset(dp, 0x00, sizeof(dp));

	for (int i = 0; i < size; ++i) {
		int64_t curr = nums[i];

		for (int r = 0; r < k; ++r) {
			dp[k + (r * curr) % k] += dp[r];
		}
		++dp[k + curr % k];
		for (int i2 = 0; i2 < k; ++i2) {
			dp[i2] = dp[i2 + k];
			dp[i2 + k] = 0;
			res[i2] += dp[i2];
		}
	}

	*ret_size = k;

	return res;
}
